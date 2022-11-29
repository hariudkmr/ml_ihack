/******************************************************************************
* File Name:   profiler_timer.c
*
* Description: This file contains the timer code used for profiling operations.
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

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "profiler_timer.h"

/******************************************************************************
* Macros
******************************************************************************/
#define TIMER_FREQUENCY_HZ  (1000000UL)

/*******************************************************************************
* Function Name: profiler_timer_init
********************************************************************************
* Summary:
*  Initialize the timer.
*
*******************************************************************************/
void profiler_timer_init(profiler_timer_t *profiler_timer)
{
    cy_rslt_t result;

    result = cyhal_timer_init(profiler_timer, (cyhal_gpio_t)CYHAL_NC_PIN_VALUE, NULL);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    cyhal_timer_set_frequency(profiler_timer, TIMER_FREQUENCY_HZ);
    cyhal_timer_cfg_t timer_config =
    {
        true,
        (cyhal_timer_direction_t)(CYHAL_TIMER_DIR_UP),
        true,
        0xFFFFFFF,
        0xFFFFFFF,
        0
    };
    cyhal_timer_configure(profiler_timer, &timer_config);
}

/* [] END OF FILE */
