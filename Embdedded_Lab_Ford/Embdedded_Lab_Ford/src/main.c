/**
 * Embedded Lab - Atmel
 * Lab A2 - Stopwatch State Machine
 * Reese Ford
 * Created: Aug 29, 2024
 * Modified: Sept 12, 2024
 * Last Commit: 9a3e7644186b884d6fc97c7add88e3b2a01736d1
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
#include <stdio.h>
#include "common.h"
#include "utilities.h"

// Display the ms time as ss.ms on the LCD
void display_stopwatch_time(uint32_t ms_value) {
	// Remove the last digit
	uint32_t seconds = 0;
	seconds = ms_value / 10;
	
	// Display modified time on LCD
	c42412a_show_numeric_dec(seconds);
	if ((ms_value/100000) >= 1) {
		c42412a_clear_icon(C42412A_ICON_DOT_3);
		c42412a_show_icon(C42412A_ICON_DOT_4);
	} else {
		c42412a_clear_icon(C42412A_ICON_DOT_4);
		c42412a_show_icon(C42412A_ICON_DOT_3);
	}
	
}

void display_clock_time(uint32_t ms_value) {
	// Add time to make 0ms = 9min 3sec
	ms_value = ms_value + 570000;
	
	// Define vars
	uint32_t min = 0;
	uint32_t sec = 0;
	uint32_t time_var = 0;
	
	sec = ms_value/1000;
	min = sec / 60;
	sec = sec % 60;
	
	time_var = (min * 100) + sec;
	
	char str[5] = "";
	sprintf(str, "%d", time_var);
	
	if (str[3] == 0) {
		char tmp[5] = "";
		tmp[1] = str[0];
		tmp[2] = str[1];
		tmp[3] = str[2];
		tmp[0] = 48;
		c42412a_show_text(tmp);
	} else {
		c42412a_show_text(str);
	}
	
	// TODO: This
	c42412a_show_icon(C42412A_ICON_COLON);
}

int main (void)
{
	board_init();
	sysclk_init();
	c42412a_init();
	
	// Configure SysTick
	uint32_t ms_length = 0;
	uint32_t freq = sysclk_get_cpu_hz();
	ms_length = 0.001/(1.0/(double)freq);
	SysTick_Config(ms_length);
	uint32_t stop_timestamp = 0;
	uint32_t pause_tickcount = 0;
	
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
			pause_tickcount = ticks - stop_timestamp;
			display_stopwatch_time(pause_tickcount);
			
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
			display_clock_time(ticks);
			// CLOCK State Changes
			if (sw1_state == GPIO_INPUT_STATE_RISING_EDGE) {
				stopwatch_state = IDLE;
				c42412a_clear_all();
			}
			break;
			
			default:
			stopwatch_state = IDLE;
			break;
		}
	}

}
