/******************************************************************************
* File Name:   profiler_timer.h
*
* Description: This file is the public interface of profiler_timer.c
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

#ifndef PROFILER_TIMER_H_
#define PROFILER_TIMER_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

/*******************************************************************************
* Typedefs
********************************************************************************/
typedef cyhal_timer_t profiler_timer_t;


/*******************************************************************************
* Function Prototypes
********************************************************************************/
void profiler_timer_init(profiler_timer_t *profiler_timer);


/*******************************************************************************
* Inline Functions
********************************************************************************/
/*******************************************************************************
* Function Name: profiler_timer_start
********************************************************************************
* Summary:
*  Start the timer.
*
*******************************************************************************/
inline void profiler_timer_start(profiler_timer_t *profiler_timer)
{
    cyhal_timer_start(profiler_timer);
}


/*******************************************************************************
* Function Name: profiler_timer_stop
********************************************************************************
* Summary:
*  Stop the timer and return the time
*
*******************************************************************************/
inline uint32_t profiler_timer_stop(profiler_timer_t *profiler_timer)
{
    cyhal_timer_stop(profiler_timer);
    uint32_t time = cyhal_timer_read(profiler_timer);
    cyhal_timer_reset(profiler_timer);
    return time;
}

#endif /* PROFILER_TIMER_H_ */

/* [] END OF FILE */
