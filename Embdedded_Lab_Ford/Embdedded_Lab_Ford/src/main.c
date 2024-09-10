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
	c42412a_init();
	
	// configure BREADBOARD_BUTTON_PIN
	ioport_set_pin_dir(BREADBOARD_BUTTON_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(BREADBOARD_BUTTON_PIN, IOPORT_MODE_PULLDOWN);
	
	// State machine state enumeration
	typedef enum{
		IDLE	= 0,
		RUNNING = 1,
		PAUSED	= 2,
		CLOCK	= 3
	}STOPWATCH_STATE_MACHINE_TYPE;
	
	STOPWATCH_STATE_MACHINE_TYPE stopwatch_state = IDLE;
	
	// Button State Variables
	GPIO_INPUT_STATE_TYPE sw0_state = GPIO_INPUT_STATE_HIGH;
	GPIO_INPUT_STATE_TYPE sw1_state = GPIO_INPUT_STATE_LOW;
	
	while (1) {
		// Check for input events
		sw0_state = check_gpio_input_state(BUTTON_0_PIN);
		sw1_state = check_gpio_input_state(BREADBOARD_BUTTON_PIN);
		
		switch(stopwatch_state) {
			case IDLE:
			// IDLE Action here
			c42412a_show_text("0");
			// IDLE State Changes
			if (sw0_state == GPIO_INPUT_STATE_FALLING_EDGE) {
				stopwatch_state = RUNNING;
			} else if (sw1_state == GPIO_INPUT_STATE_RISING_EDGE) {
				stopwatch_state = CLOCK;
			}
			break;
			
			case RUNNING:
			// RUNNING Action here
			c42412a_show_text("1");
			// RUNNING State Changes
			if (sw0_state == GPIO_INPUT_STATE_FALLING_EDGE) {
				stopwatch_state = PAUSED;
			}
			break;
			
			case PAUSED:
			// PAUSED Action here
			c42412a_show_text("2");
			// PAUSED State Changes
			if (sw0_state == GPIO_INPUT_STATE_FALLING_EDGE) {
				stopwatch_state = RUNNING;
			} else if (sw1_state == GPIO_INPUT_STATE_RISING_EDGE) {
				stopwatch_state = IDLE;
			}
			break;
			
			case CLOCK:
			// CLOCK Action here
			c42412a_show_text("3");
			// CLOCK State Changes
			if (sw1_state == GPIO_INPUT_STATE_RISING_EDGE) {
				stopwatch_state = IDLE;
			}
			break;
			
			default:
			stopwatch_state = IDLE;
			break;
		}
	}

}
