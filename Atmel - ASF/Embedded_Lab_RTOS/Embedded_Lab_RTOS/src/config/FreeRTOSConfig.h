/*
    FreeRTOS V6.0.2 - Copyright (C) 2010 Real Time Engineers Ltd.

    ***************************************************************************
    *                                                                         *
    * If you are:                                                             *
    *                                                                         *
    *    + New to FreeRTOS,                                                   *
    *    + Wanting to learn FreeRTOS or multitasking in general quickly       *
    *    + Looking for basic training,                                        *
    *    + Wanting to improve your FreeRTOS skills and productivity           *
    *                                                                         *
    * then take a look at the FreeRTOS eBook                                  *
    *                                                                         *
    *        "Using the FreeRTOS Real Time Kernel - a Practical Guide"        *
    *                  http://www.FreeRTOS.org/Documentation                  *
    *                                                                         *
    * A pdf reference manual is also available.  Both are usually delivered   *
    * to your inbox within 20 minutes to two hours when purchased between 8am *
    * and 8pm GMT (although please allow up to 24 hours in case of            *
    * exceptional circumstances).  Thank you for your support!                *
    *                                                                         *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/
#if defined (__GNUC__) || defined (__ICCARM__) || defined(__CC_ARM)
#   include "sysclk.h"
#endif

//#define configUSE_PREEMPTION                     1
#define configUSE_PREEMPTION                       0
#define configUSE_IDLE_HOOK                        1
#define configUSE_TICK_HOOK                        1
#define configCPU_CLOCK_HZ                         (sysclk_get_cpu_hz())
#define configTICK_RATE_HZ                         ((portTickType) 1000)
#define configMINIMAL_STACK_SIZE                   ((unsigned short) 70)
#define configTOTAL_HEAP_SIZE                    ((size_t) ( 0x2C00-600 ))
#define configMAX_TASK_NAME_LEN                    ( 16 )
#define configUSE_TRACE_FACILITY                   1
#define configUSE_16_BIT_TICKS                     0
#define configIDLE_SHOULD_YIELD                    0
#define configUSE_CO_ROUTINES                      0
#define configUSE_MUTEXES                          1
#define configUSE_RECURSIVE_MUTEXES                0
#define configCHECK_FOR_STACK_OVERFLOW             2
#define configGENERATE_RUN_TIME_STATS              0
#define configENABLE_BACKWARD_COMPATIBILITY        1

#define configMAX_PRIORITIES                       (5)
#define configMAX_CO_ROUTINE_PRIORITIES            (2)
#define configQUEUE_REGISTRY_SIZE                  10

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet                   1
#define INCLUDE_uxTaskPriorityGet                  0
#define INCLUDE_vTaskDelete                        0
#define INCLUDE_vTaskCleanUpResources              0
#define INCLUDE_vTaskSuspend                       1
#define INCLUDE_vTaskDelayUntil                    1
#define INCLUDE_vTaskDelay                         1
#define INCLUDE_uxTaskGetStackHighWaterMark        1

#define configKERNEL_INTERRUPT_PRIORITY            (0x0f << 4) /* Priority 15, or 255 as only the top four bits are implemented.  This is the lowest priority. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY       (0x05 << 4) /* Priority 5, or 80 as only the top four bits are implemented. */
#define configUSE_STATS_FORMATTING_FUNCTIONS 1
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define xPortPendSVHandler PendSV_Handler
#define vPortSVCHandler SVC_Handler
#define xPortSysTickHandler SysTick_Handler
#endif /* FREERTOS_CONFIG_H */
