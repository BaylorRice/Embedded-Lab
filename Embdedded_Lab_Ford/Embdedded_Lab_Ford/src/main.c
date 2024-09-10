/**
 * Embedded Lab - Atmel
 * Lab A2 - Stopwatch State Machine
 * Reese Ford
 * Created: Aug 29, 2024
 * Modified: Sept 10, 2024
 * Last Commit: 
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "common.h"
#include "utilities.h"

int main (void)
{
	board_init();
	
	// State machine state enumeration
	typedef enum{
		IDLE	= 0,
		RUNNING = 1,
		PAUSED	= 2,
		CLOCK	= 3
	}STOPWATCH_STATE_MACHINE_TYPE;
	
	// Variables
	
	while (1) {
		
	}

}
