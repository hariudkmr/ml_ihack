/******************************************************************************
* File Name:   audio_task.h
*
* Description: This file is the public interface of audio_task.c. This file 
*              also contains the configuration parameters used in the audio_task.
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

#ifndef AUDIO_TASK_H_
#define AUDIO_TASK_H_

#include "cybsp.h"
#include "mfcc_data.h"
#include "arm_math.h"
#include "arm_const_structs.h"

/*******************************************************************************
* Macros
********************************************************************************/
/* Enable profiler that prints out time taken for various tasks and operations */
#define PROFILER_ENABLE                             (1u)

/* Define how many samples in a frame */
#define TBUFFER_SIZE                                 65536
#define SBUFFER_SIZE                                 16384
#define N_FRAMES                                     4

/* Desired sample rate. Typical values: 8/16/22.05/32/44.1/48kHz */
#define SAMPLE_RATE_HZ                              16000u

/* Decimation Rate of the PDM/PCM block. Typical value is 64 */
#define DECIMATION_RATE                             64u

/* Audio Subsystem Clock. Typical values depends on the desire sample rate:
- 8/16/48kHz    : 24.576 MHz
- 22.05/44.1kHz : 22.579 MHz */
#define AUDIO_SYS_CLOCK_HZ                          24576000u

/* PDM/PCM Pins */
#define PDM_DATA                                    P10_5
#define PDM_CLK                                     P10_4

/* PDM capture mode - stereo, left, or right
 *      Valid choices: CYHAL_PDM_PCM_MODE_STEREO, CYHAL_PDM_PCM_MODE_LEFT, CYHAL_PDM_PCM_MODE_RIGHT 
 */
#define PDM_MODE                                    (CYHAL_PDM_PCM_MODE_LEFT)

/* PDM mic gain */
#define PDM_GAIN_LEFT                               (5u)
#define PDM_GAIN_RIGHT                              (5u)

/* Spectrogram parameters */
#define FFT_STEP_SIZE                               (1024u)
#define FFT_OUTPUT_SIZE                             (DCT_OUTPUT_LEN)

/* Note: There are a few spectrogram parameters are generated and defined as part of 
 *       MFCC Data generation scripts. The definitions are available in "mfcc_data.h" file.
 *
 *       FFT_LEN, DCT_OUTPUT_LEN, MEL_FILTERS_LEN, MIN_FREQUENCY_HZ, MAX_FREQUENCY_HZ
 */

/* Spectrogram parameters */
#define SPECTROGRAM_NUM_SAMPLES                     (SBUFFER_SIZE) /* Specify as multiple of 'BUFFER_SIZE' */

/* Sizes for various buffers created in the application */
#define NUM_FRAMES_IN_SPECTROGRAM                   (SPECTROGRAM_NUM_SAMPLES / FFT_STEP_SIZE)

#define SPECTROGRAM_HEIGHT                          (NUM_FRAMES_IN_SPECTROGRAM)
#define SPECTROGRAM_WIDTH                           (FFT_OUTPUT_SIZE)


/*******************************************************************************
* Type Definitions
********************************************************************************/
typedef float32_t                           spect_t;
typedef float32_t                           pcm_t;
typedef float32_t                           tmp_buf_t;
typedef arm_mfcc_instance_f32               mfcc_instance_t;

/*******************************************************************************
* Function Prototypes
********************************************************************************/
void audio_task_init(void);
void audio_task_loop(void);

#endif /* AUDIO_TASK_H_ */

/* [] END OF FILE */
