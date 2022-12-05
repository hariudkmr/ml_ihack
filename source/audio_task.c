/******************************************************************************
* File Name:   audio_task.c
*
* Description: This file contains all the functions and variables used for 
*              audio data acquisition and processing.
*
* Related Document: See README.md
*
*
*******************************************************************************
* Copyright 2022, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#include "audio_task.h"
#include "inference_task.h"
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

#include "arm_math.h"
#include "arm_const_structs.h"
#include <math.h>

#include "mfcc_data.h"

#if PROFILER_ENABLE
    #include "profiler_timer.h"
#endif /* PROFILER_ENABLE */

#include "json_print.h"

/******************************************************************************
* Macros
******************************************************************************/
#define PCM_NORMALISE_F32(X)                            ((X > 0.0f) ? (X / (float32_t)32767.0f) : (X / (float32_t)32768.0f))

/* DC Filter related constants */
#define A1                                              32511 // (1-2^(-7)) Q32:1.31
#define MAX_SIGN_POS_PCMBIT_SIZE                        32768
#define MAX_SIGN_NEG_PCMBIT_SIZE                        -32768

#if PROFILER_ENABLE
    #define PCM_PROFILER_START()                        profiler_timer_start(&pcm_timer)
    #define PCM_PROFILER_STOP()                         printf("\n\n\nPCM Samples received after %lu ms\n", profiler_timer_stop(&pcm_timer))

    #define TOTAL_PREPROCESSING_PROFILER_START()        profiler_timer_start(&total_timer)
    #define TOTAL_PREPROCESSING_PROFILER_STOP()         printf("\nTotal Preprocessing time: %lu us\n", profiler_timer_stop(&total_timer))

    #define OPERATION_PROFILER_START()                  profiler_timer_start(&individual_timer)
    #define OPERATION_PROFILER_STOP(X)                  printf(X " time: %lu us\n", profiler_timer_stop(&individual_timer))
#else
    #define PCM_PROFILER_START()
    #define PCM_PROFILER_STOP()

    #define TOTAL_PREPROCESSING_PROFILER_START()
    #define TOTAL_PREPROCESSING_PROFILER_STOP()

    #define OPERATION_PROFILER_START()
    #define OPERATION_PROFILER_STOP(X)
#endif /* PROFILER_ENABLE */


/*******************************************************************************
* Global Variables
********************************************************************************/
/* PCM buffers and pointers */
static int16_t  rx_buffer0[BUFFER_SIZE] = {0};
static int16_t  rx_buffer1[BUFFER_SIZE] = {0};
static pcm_t    final_pcm_buffer[BUFFER_SIZE] = {0};
static int16_t* active_rx_buffer;
static int16_t* full_rx_buffer;

/* Interrupt flags */
volatile bool pdm_pcm_flag = false;

/* HAL Object */
static cyhal_pdm_pcm_t pdm_pcm;
static cyhal_clock_t   audio_clock;
static cyhal_clock_t   pll_clock;

/* HAL Config for PDM/PCM block */
static const cyhal_pdm_pcm_cfg_t pdm_pcm_cfg = 
{
    .sample_rate     = SAMPLE_RATE_HZ,
    .decimation_rate = DECIMATION_RATE,
    .mode            = PDM_MODE, 
    .word_length     = 16,                  /* bits */
    .left_gain       = PDM_GAIN_LEFT,       /* x 0.5 dB */
    .right_gain      = PDM_GAIN_RIGHT,      /* x 0.5 dB */
};

/* MFCC instance */
static mfcc_instance_t mfcc;

/* Spectrogram buffer */
static spect_t spectrogram_final_buffer[SPECTROGRAM_HEIGHT][SPECTROGRAM_WIDTH] = {0};
uint32_t spectrogram_buffer_index = 0;
static spect_t *final_spectrogram_ptr;
static uint32_t final_spectrogram_num_samples = 0;

/* Standardized buffer */
static spect_t standardized_spectrogram[SPECTROGRAM_HEIGHT][SPECTROGRAM_WIDTH] = {0};

/* Variables used for DC filtering */
static int16_t x_prev = 0;
static tmp_buf_t y_prev = 0;

#if PROFILER_ENABLE
    /* Profiler timer instances */
    static profiler_timer_t pcm_timer, total_timer, individual_timer;
#endif /* PROFILER_ENABLE */


/*******************************************************************************
* Function Prototypes
********************************************************************************/
static void pdm_pcm_isr_handler(void *arg, cyhal_pdm_pcm_event_t event);
static void clock_init(void);

static void mfcc_init(void);
static uint32_t get_buffer_mfcc_spectrogram(pcm_t *input_buffer, uint32_t input_buffer_size);
static void get_standardized_spectrogram(uint32_t input_height, uint32_t input_width, spect_t *input_buffer, spect_t *output_buffer);

static inline pcm_t iir_dc_filter(int16_t pcm_input);
static void pcm_dc_filtering(int16_t *pcm_input, pcm_t *filtered_output, uint32_t num_samples);


/*******************************************************************************
* Function Name: audio_task_init
********************************************************************************
* Summary:
*  Function that initializes the audio task. 
*   - Sets up the audio clocks, MFCC instance, and PDM/PCM hardware block
*   - Starts the PDM/PCM block.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void audio_task_init(void)
{
    /* Init the clocks */
    clock_init();

    /* Initialize the MFCC Instance */
    mfcc_init();

    #if PROFILER_ENABLE
        /* Init the timers to measure operation times. */
        profiler_timer_init(&pcm_timer);
        profiler_timer_init(&total_timer);
        profiler_timer_init(&individual_timer);
    #endif /* PROFILER_ENABLE */

    /* Initialize the PDM/PCM block and set-up the interrupts. */
    cyhal_pdm_pcm_init(&pdm_pcm, PDM_DATA, PDM_CLK, &audio_clock, &pdm_pcm_cfg);
    cyhal_pdm_pcm_register_callback(&pdm_pcm, pdm_pcm_isr_handler, NULL);
    cyhal_pdm_pcm_enable_event(&pdm_pcm, CYHAL_PDM_PCM_ASYNC_COMPLETE, CYHAL_ISR_PRIORITY_DEFAULT, true);
    cyhal_pdm_pcm_set_async_mode(&pdm_pcm, CYHAL_ASYNC_SW,CYHAL_DMA_PRIORITY_DEFAULT);

    /* Setup the PCM buffer pointers and start the PDM hardware block */
    active_rx_buffer = rx_buffer0;
    full_rx_buffer   = rx_buffer1;
    cyhal_pdm_pcm_start(&pdm_pcm);

    /* Start async read to read frame after 1 sec delay for stabilization */
    cyhal_system_delay_ms(1000u);
    PCM_PROFILER_START();
    //cyhal_pdm_pcm_read_async(&pdm_pcm, active_rx_buffer, BUFFER_SIZE);
}

/*******************************************************************************
* Function Name: audio_task_loop
********************************************************************************
* Summary:
*  Infinite loop that processes the PCM samples received from PDM block upon 
*  interrupt and then invokes the inferencing function for ML inferencing.
*
*  Preprocessing of audio data include:
*   - Filtering to remove DC from the PCM samples
*   - Compute the MFCC spectrogram for the filtered PCM samples
*   - Standardize the spectrogram (Scale the spectrogram to have mean 0 & variance 1)
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void audio_task_loop(void)
{
    for(;;)
    {
        /* Check if any microphone has data to process */
        if (pdm_pcm_flag)
        {
            PCM_PROFILER_STOP();

            /* Clear the PDM/PCM flag */
            pdm_pcm_flag = 0;

            /* Swap the active and the next rx buffers */
            //int16_t *temp    = active_rx_buffer;
            //active_rx_buffer = full_rx_buffer;
            //full_rx_buffer   = temp;

            TOTAL_PREPROCESSING_PROFILER_START();

            /**********************************************************************
             ============================ DC Filtering ============================
            **********************************************************************/
            OPERATION_PROFILER_START();

            /* IIR filter to remove DC component from the PCM samples */
            pcm_dc_filtering(full_rx_buffer, final_pcm_buffer, BUFFER_SIZE);

            OPERATION_PROFILER_STOP("  DC Filtering");


            /**********************************************************************
             ========================== MFCC Spectrogram ==========================
            **********************************************************************/
            OPERATION_PROFILER_START();

            get_buffer_mfcc_spectrogram(final_pcm_buffer, (sizeof(final_pcm_buffer) / sizeof(final_pcm_buffer[0])));

            OPERATION_PROFILER_STOP("    MFCC Spectrogram");
            final_spectrogram_ptr = (spect_t *) spectrogram_final_buffer;
            final_spectrogram_num_samples = SPECTROGRAM_HEIGHT * SPECTROGRAM_WIDTH;


            /**********************************************************************
             ==================== Spectrogram Standardization =====================
            **********************************************************************/
            OPERATION_PROFILER_START();

            /* Standardize the spectrogram */
            get_standardized_spectrogram(SPECTROGRAM_HEIGHT, 
                                         SPECTROGRAM_WIDTH, 
                                         (spect_t *)spectrogram_final_buffer, 
                                         (spect_t *)standardized_spectrogram);

            OPERATION_PROFILER_STOP("      Spectrogram Standardization");
            final_spectrogram_ptr = (spect_t *) standardized_spectrogram;


            /* ====================== END OF PREPROCESSING ====================== */
            TOTAL_PREPROCESSING_PROFILER_STOP();


            /**********************************************************************
             ======================= ML Model Inferencing  ========================
            **********************************************************************/
            OPERATION_PROFILER_START();
            inference_task(final_spectrogram_ptr);
            OPERATION_PROFILER_STOP("\nML Inferencing");


            /**********************************************************************
             ====================== PDM/PCM Read Next Buffer ======================
            **********************************************************************/
            /* Start reading into the next buffer...
            *  Note: This should ideally be done at the start before preprocessing 
            *        so that we don't miss any audio samples 
            */
            //cyhal_pdm_pcm_read_async(&pdm_pcm, active_rx_buffer, BUFFER_SIZE);
            //PCM_PROFILER_START();

        }
    }
}


/*******************************************************************************
* Function Name: pdm_pcm_isr_handler
********************************************************************************
* Summary:
*  PDM/PCM ISR handler. Set a flag to be processed in the main loop.
*
* Parameters:
*  arg: not used
*  event: event that occurred
*
* Return:
*  None
*
*******************************************************************************/
static void pdm_pcm_isr_handler(void *arg, cyhal_pdm_pcm_event_t event)
{
    /* To avoid compiler warnings */
    (void) arg;
    PCM_PROFILER_STOP(); 
    if (0u != (event & CYHAL_PDM_PCM_ASYNC_COMPLETE))
    {
        PCM_PROFILER_START();
        pdm_pcm_flag = true;
        uint32_t* temp = active_rx_buffer;
        active_rx_buffer = full_rx_buffer;
        full_rx_buffer   = temp;
        // Start reading into the next buffer while the just-filled one is being processed
        //cyhal_pdm_pcm_read_async(&pdm_pcm, active_rx_buffer, BUFFER_SIZE);
    }
    PCM_PROFILER_START();
}

/*******************************************************************************
* Function Name: clock_init
********************************************************************************
* Summary:
*  Initialize the clocks in the system.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void clock_init(void)
{
    /* Initialize the PLL */
    cyhal_clock_get(&pll_clock, &CYHAL_CLOCK_PLL[0]);
    cyhal_clock_init(&pll_clock);
    cyhal_clock_set_frequency(&pll_clock, AUDIO_SYS_CLOCK_HZ, NULL);
    cyhal_clock_set_enabled(&pll_clock, true, true);

    /* Initialize the audio subsystem clock (CLK_HF[1]) 
     * The CLK_HF[1] is the root clock for the I2S and PDM/PCM blocks */
    cyhal_clock_get(&audio_clock, &CYHAL_CLOCK_HF[1]);
    cyhal_clock_init(&audio_clock);

    /* Source the audio subsystem clock from PLL */
    cyhal_clock_set_source(&audio_clock, &pll_clock);
    cyhal_clock_set_enabled(&audio_clock, true, true);
}

/*******************************************************************************
* Function Name: mfcc_init
********************************************************************************
* Summary:
*  Initialize the MFCC instance with appropriate configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void mfcc_init(void)
{
    arm_status arm_result = ARM_MATH_SUCCESS;

    memset(&mfcc, 0, sizeof(mfcc));

    arm_result = arm_mfcc_init_f32(&mfcc,
                                   FFT_LEN,
                                   MEL_FILTERS_LEN,
                                   DCT_OUTPUT_LEN,
                                   MFCC_DCT_COEFS,
                                   MFCC_FILTER_POS,
                                   MFCC_FILTER_LEN,
                                   MFCC_FILTER_COEFS,
                                   MFCC_WINDOW_COEFS);

    /* If the operation failed stop the program execution */
    CY_ASSERT(arm_result == ARM_MATH_SUCCESS);
}


/*******************************************************************************
* Function Name: get_buffer_mfcc_spectrogram
********************************************************************************
* Summary:
*  Function that computes the MFCC spectrogram for the entire buffer of PCM data.
*
* Parameters:
*  input_buffer: Pointer to the PCM buffer for which the MFCC is to be computed.
*                Note: The size of the above buffer should be atleast 'BUFFER_SIZE'.
*
* Return:
*  None
*
*******************************************************************************/
static uint32_t get_buffer_mfcc_spectrogram(pcm_t *input_buffer, uint32_t input_buffer_size)
{
    /* Temporary buffers */
    tmp_buf_t temp_buffer[2*(FFT_LEN + 10u)] = {0};
    pcm_t temp_input[FFT_LEN + 5u] = {0};

    /* Reset the index to zero every time */
    spectrogram_buffer_index = 0;

    /* Start of PCM buffer */
    pcm_t *pcm_data_start = input_buffer;

    /* The last starting point of PCM buffer to compute last FFT in this buffer */
    pcm_t *pcm_data_end = input_buffer + input_buffer_size - FFT_LEN;

    /* Compute the MFCC Spectrogram for every frame in the buffer */
    while(pcm_data_start <= pcm_data_end)
    {
        /* Copy 'FFT_LEN' samples from input buffer to temp input buffer. This
         * is done because the MFCC API (arm_mfcc_f32) modifies the source 
         * buffer and we don't want the input buffer to change.
         */
        memcpy(temp_input, pcm_data_start, (sizeof(pcm_t) * FFT_LEN));
        arm_mfcc_f32(&mfcc, 
                     temp_input,
                     (spect_t *) &(spectrogram_final_buffer[spectrogram_buffer_index++]), 
                     temp_buffer);
        pcm_data_start += FFT_STEP_SIZE;
    }

    return (pcm_data_start - pcm_data_end);
}

/*******************************************************************************
* Function Name: get_standardized_spectrogram
********************************************************************************
* Summary:
*   Linearly scales the spectrogram image to have mean 0 and variance 1.
*   Reference: https://www.tensorflow.org/api_docs/python/tf/image/per_image_standardization
*
*   For each pixel x in image, compute (x - mean) / adjusted_stddev, where
*       - mean is the average of all values in the image
*       - adjusted_stddev = max(stddev, 1.0/sqrt(N)) is capped away from 0 to 
*           protect against division by 0 when handling uniform images
*               - N is the number of elements in the image
*               - stddev is the standard deviation of all values in the image
*
* Parameters:
*  input_height : Number of rows in the input image 'input_buffer'
*  input_width  : Number of columns in the input image 'input_buffer'
*  input_buffer : Pointer to the input image buffer
*  output_buffer: Pointer to the output buffer
*
* Return:
*  None
*
*******************************************************************************/
static void get_standardized_spectrogram(uint32_t input_height, uint32_t input_width, spect_t *input_buffer, spect_t *output_buffer)
{
    spect_t mean = 0, std_dev = 0, adjusted_stddev = 0;
    float32_t sqrt_1_n = 0.0f;
    float32_t temp_buffer[FFT_OUTPUT_SIZE] = {0};

    uint32_t num_samples = input_height * input_width;
    spect_t *input_ptr = input_buffer;
    spect_t *output_ptr = output_buffer;

    memset(output_ptr, 0, sizeof(spect_t) * input_height * input_width);

    arm_mean_f32(input_buffer, num_samples, &mean);
    arm_std_f32(input_buffer, num_samples, &std_dev);
    arm_sqrt_f32((float32_t)num_samples, &sqrt_1_n);
    sqrt_1_n = 1.0f / sqrt_1_n;
    adjusted_stddev = (std_dev > sqrt_1_n) ? std_dev : sqrt_1_n;

    for (uint32_t i = 0; i < input_height; i++)
    {
        for (uint32_t j = 0; j < input_width; j++)
        {
            temp_buffer[j] = ((float32_t) *(input_ptr) - (float32_t)mean) / (float32_t)adjusted_stddev;
            input_ptr ++;
        }

        memcpy(output_ptr, temp_buffer, sizeof(spect_t) * input_width);
        output_ptr += input_width;
    }
}


/*******************************************************************************
* Function Name: iir_dc_filter
********************************************************************************
* Summary:
*  Simple IIR filter implementation for DC filtering of PCM stream.
*
*  This function takes in one PCM sample and returns one sample as filtered 
*  output. It also remembers the previous input and previous output.
*
*  Reference: https://www.knowles.com/docs/default-source/default-document-library/dc-blocking-filter.pdf 
*
*
* Parameters:
*  pcm_input: Current PCM sample to be filtered
*
* Return:
*  Filtered PCM sample of type 'pcm_t'
*
*******************************************************************************/
static inline pcm_t iir_dc_filter(int16_t pcm_input)
{
    int16_t input, delta_x;
    pcm_t output;
    tmp_buf_t a1_y_prev;

    input = (int16_t) pcm_input;
    delta_x = input - x_prev;
    a1_y_prev = A1 * y_prev / MAX_SIGN_POS_PCMBIT_SIZE;
    output = delta_x + (pcm_t) a1_y_prev;

    x_prev = input;
    y_prev = (tmp_buf_t) output;
    output = PCM_NORMALISE_F32(output);

    return output;
}

/*******************************************************************************
* Function Name: pcm_dc_filtering
********************************************************************************
* Summary:
*  Function that handles the DC filtering of the PCM buffer.
*
*  This function calls the iir_dc_filter() function for each sample in the 
*  input buffer and stores it in the output buffer.
*
* Parameters:
*  pcm_input        : Pointer to the input PCM buffer that needs to be filtered
*  filtered_output  : Pointer to the output PCM buffer
*  num_samples      : Number of samples to be filtered in 'pcm_input' buffer
*
* Return:
*  None
*
*******************************************************************************/
static void pcm_dc_filtering(int16_t *pcm_input, pcm_t *filtered_output, uint32_t num_samples)
{
    int16_t *input_ptr = pcm_input;
    pcm_t *output_ptr = filtered_output;

    do
    {
        /* Loop unrolling by factor '16' */
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);

        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);

        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);

        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);

        num_samples -= 16;
    }
    while (num_samples >= 16);

    /* Process the remaining samples if any */
    while (num_samples > 0)
    {
        *(output_ptr)++ = iir_dc_filter(*(input_ptr)++);
        num_samples --;
    }
}

/* [] END OF FILE */
