/******************************************************************************
* File Name:   inference_task.c
*
* Description: This file contains the task that handles all the functions 
*              required for ML inferencing.
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

#include "inference_task.h"

#include "audio_task.h"
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

#include "mtb_ml_utils.h"
#include "mtb_ml_common.h"
#include "mtb_ml_model.h"
#include "stdlib.h"
#include "json_print.h"

/* Including ML include file with macro */
#include MTB_ML_INCLUDE_MODEL_FILE(MODEL_NAME)

#if JSON_RESULTS_PRINTING
    #include "profiler_timer.h"
#endif /* JSON_RESULTS_PRINTING */

/*******************************************************************************
* Global Variables
********************************************************************************/
/* ML model information */
mtb_ml_model_t *kws_obj;

/* ML variables */
mtb_ml_model_bin_t kws_bin = { MTB_ML_MODEL_BIN_DATA(MODEL_NAME) };

int model_output_size = 0;
int class_index = 0;

MTB_ML_DATA_T *result_buffer;

/* The order of classes is important. This needs to match the order in the jupyter notebook */
char classes[6][10] = {"marvin", "off", "on", "one", "three", "two" };

/* Fill this based on the order in the above classes array */
const int marvin_class_index = 0;
const int off_class_index = 1;
const int on_class_index = 2;
const int one_class_index = 3;
const int three_class_index = 4;
const int two_class_index = 5;

#if JSON_RESULTS_PRINTING
    /* Profiler timer instance to measure time between successive inferences */
    static profiler_timer_t inference_timer;
    static uint32_t inference_time_us;
#endif /* JSON_RESULTS_PRINTING */

/*******************************************************************************
* Function Name: inference_task_init
********************************************************************************
* Summary:
*  Function that initializes the inference task.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void inference_task_init(void)
{
    /* Status variable to indicate the result of various operations */
    cy_rslt_t result;

    /* Initialize the User LED */
    cyhal_gpio_init(CYBSP_USER_LED, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);

    result = mtb_ml_model_init(&kws_bin, NULL, &kws_obj);

    if (CY_RSLT_SUCCESS != result) 
    {
           printf("MTB Model Init failed \r\n");
           return;
       }

    model_output_size = mtb_ml_model_get_output_size(kws_obj);
    printf("Model Output Size %d \r\n", model_output_size);

    result_buffer = (MTB_ML_DATA_T *) malloc(model_output_size * sizeof(MTB_ML_DATA_T));

    printf("Sizeof MTB_ML_DATA_T is %d \r\n", sizeof(MTB_ML_DATA_T));
    printf("Type of quantization is %d\r\n", sizeof(MTB_ML_DATA_T) * 8);

    #if JSON_RESULTS_PRINTING
        profiler_timer_init(&inference_timer);
    #endif /* JSON_RESULTS_PRINTING */

    printf("Inferencing task initialized!\r\n");
}

/*******************************************************************************
* Function Name: inference_task
********************************************************************************
* Summary:
*  Function that performs the inferencing using the spectrogram data and 
*  prints the results.
*
* Parameters:
*  spectrogram_ptr: Pointer to the spectrogram image buffer
*
* Return:
*  None
*
*******************************************************************************/
void inference_task(spect_t *spectrogram_ptr)
{
    #if JSON_RESULTS_PRINTING
        profiler_timer_start(&inference_timer);
        inference_time_us = profiler_timer_stop(&inference_timer);
        profiler_timer_start(&inference_timer);
    #endif /* JSON_RESULTS_PRINTING */

    memset(result_buffer, 0, model_output_size * sizeof(MTB_ML_DATA_T));

    mtb_ml_model_run(kws_obj, (MTB_ML_DATA_T*) spectrogram_ptr, result_buffer);

    class_index = mtb_ml_utils_find_max(result_buffer, model_output_size);

    if (result_buffer[class_index] > INFERENCE_THRESHOLD_PROBABILITY)
    {
        printf("\n Predicted Class = %10s Confidence %.2f \r\n", classes[class_index], result_buffer[class_index]);
    }
    else 
    {
        //printf("Low Confidence score < 0.8, actual confidence %.2f - Marked as unknown \r\n", result_buffer[class_index]);
    }

    #if JSON_RESULTS_PRINTING
        print_json_output(0, 0, inference_time_us);
    #endif
}

/* [] END OF FILE */
