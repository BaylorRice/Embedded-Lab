/*
 * Embedded Lab - Atmel RTOS
 * Lab A5 - FreeRTOS
 * Reese Ford
 * Using code provided by Steven Potter
 * Created: Oct 8, 2024
 * Modified: Oct 10, 2024
 * Last Commit: 816e31a31dec7a5cb55248e5cee9862561548433
*/

/**
 * \file
 *
 * \brief FreeRTOS configuration
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
 
/**
 * \mainpage FreeRTOS Real Time Kernel example
 *
 * \section Purpose
 *
 * The FreeRTOS example will help users how to use FreeRTOS in SAM boards.
 * This basic application shows how to create task and get information of
 * created task.
 *
 * \section Requirements
 *
 * This package can be used with SAM boards.
 *
 * \section Description
 *
 * The demonstration program create two task, one is make LED on the board
 * blink at a fixed rate, and another is monitor status of task.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.microchip.com/dyn/resources/prod_documents/doc6224.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://ww1.microchip.com/downloads/en/appnotes/doc6310.pdf">
 *    GNU-Based Software Development</a>
 *    application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>,
 *    depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# LED should start blinking on the board. In the terminal window, the
 *    following text should appear (values depend on the board and chip used):
 *    \code
	-- Freertos Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 *
 */

#include <asf.h>
#include "conf_board.h"
#include "common.h"
#include "utilities.h"
#include "utilities_tc.h"
#include "rtos_tasks.h"

#define TASK_MONITOR_STACK_SIZE            (2048/sizeof(portSTACK_TYPE))
#define TASK_MONITOR_STACK_PRIORITY        (tskIDLE_PRIORITY)
#define TASK_LED_STACK_SIZE                (1024/sizeof(portSTACK_TYPE))
#define TASK_LED_STACK_PRIORITY            (tskIDLE_PRIORITY)

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,
		signed char *pcTaskName);
extern void vApplicationIdleHook(void);
extern void vApplicationTickHook(void);
extern void vApplicationMallocFailedHook(void);
extern void xPortSysTickHandler(void);

/**
 * \brief Called if stack overflow during execution
 */
extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,
		signed char *pcTaskName)
{
	printf("stack overflow %x %s\r\n", pxTask, (portCHAR *)pcTaskName);
	/* If the parameters have been corrupted then inspect pxCurrentTCB to
	 * identify which task has overflowed its stack.
	 */
	for (;;) {
	}
}

/**
 * \brief This function is called by FreeRTOS idle task
 */
extern void vApplicationIdleHook(void)
{
	//printf("I");
}

/**
 * \brief This function is called by FreeRTOS each tick
 */
extern void vApplicationTickHook(void)
{
	//printf("T");
	
}

extern void vApplicationMallocFailedHook(void)
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

	/* Force an assert. */
	configASSERT( ( volatile void * ) NULL );
}



/**
 *  \brief FreeRTOS Real Time Kernel example entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();
	ioport_set_pin_dir(BREADBOARD_LED_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(SW1_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(SW1_PIN, IOPORT_MODE_PULLDOWN);
	
	ioport_enable_pin(SW2_PIN);
	ioport_set_pin_dir(SW2_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(SW2_PIN, IOPORT_MODE_PULLDOWN);	
	
	ioport_set_pin_dir(EXT1_PIN_5, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(EXT1_PIN_6, IOPORT_DIR_OUTPUT);
	
	
	/* Initialize the console uart */
	configure_console();
	printf("Program Starting\r\n");
	
	c42412a_init();
	
	ioport_set_pin_mode(SERVO_CTRL_PIN, PIN_TC_WAVEFORM_MUX);
	/** Disable I/O to enable peripheral mode) */
	ioport_disable_pin(SERVO_CTRL_PIN);
	tc_waveform_initialize();


	if (xTaskCreate(task_check_buttons, "Check Buttons", TASK_LED_STACK_SIZE, NULL,
	0, NULL) != pdPASS) {
		printf("Failed to create Check Buttons Task\r\n");
	}

	if (xTaskCreate(task_update_position, "Update Position", TASK_MONITOR_STACK_SIZE, NULL,
	2, NULL) != pdPASS) {
		printf("Failed to create Update Position Task\r\n");
	}
	
	/* Start the scheduler. */
	vTaskStartScheduler();

	/* Will only get here if there was insufficient memory to create the idle task. */
	return 0;
}
