/**
 * Embedded Lab - Atmel
 * Two Button Test
 * Reese Ford
 * Created: Aug 29, 2024
 * Modified: Oct 01, 2024
 * Last Commit: 6d13b4c454df58c02b571a31d0fe71daade66460
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

// Defining function prototypes so systick can use them
void display_stopwatch_time(uint32_t);
void display_clock_time(uint32_t);
void display_temp(float, TEMPERATURE_UNIT_TYPE);

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
	
	c42412a_show_icon(C42412A_ICON_COLON);
}

void display_temp(float temp, TEMPERATURE_UNIT_TYPE unit) {
	c42412a_show_numeric_dec(temp_val*1000);
	c42412a_show_icon(C42412A_ICON_DOT_3);
	if (unit == TEMPERATURE_UNIT_FAHRENHEIT) {
		c42412a_clear_icon(C42412A_ICON_DEGREE_C);
		c42412a_show_icon(C42412A_ICON_DEGREE_F);
	} else if (unit == TEMPERATURE_UNIT_CELSIUS) {
		c42412a_clear_icon(C42412A_ICON_DEGREE_F);
		c42412a_show_icon(C42412A_ICON_DEGREE_C);
	}
}

int main (void)
{
	board_init();

	// Configure Breadboard LED
	configure_bread_led(BREADBOARD_LED_PIN);

	// configure button 1
	configure_bread_button(BREADBOARD_BUTTON1_PIN);
	configure_bread_button(BREADBOARD_BUTTON2_PIN);
	
	// Define State Machine
	typedef enum {
		STATE_LED_OFF = 0,
		STATE_LED_ON = 1
	}RSNOR_STATE_TYPE;
	RSNOR_STATE_TYPE program_state = STATE_LED_OFF;
	
	// Define button level variables
	GPIO_INPUT_STATE_TYPE button1_level = GPIO_INPUT_STATE_LOW;
	GPIO_INPUT_STATE_TYPE button2_level = GPIO_INPUT_STATE_LOW;
	GPIO_INPUT_STATE_TYPE button0_level = GPIO_INPUT_STATE_LOW;


	while (1)
	{
		// Read buttons
		button1_level = read_bread_button(BREADBOARD_BUTTON1_PIN);
		button2_level = read_bread_button(BREADBOARD_BUTTON2_PIN);
		button0_level = read_bread_button(BUTTON_0_PIN);
		
		switch(program_state) {
			case STATE_LED_OFF:
				set_bread_led(BREADBOARD_LED_PIN, LED_STATE_OFF);
				if (button1_level == GPIO_INPUT_STATE_RISING_EDGE) {
					program_state = STATE_LED_ON;
				}
				if (button0_level == GPIO_INPUT_STATE_FALLING_EDGE) {
					program_state = STATE_LED_ON;
				}
				break;
			case STATE_LED_ON:
				set_bread_led(BREADBOARD_LED_PIN, LED_STATE_ON);
				if (button2_level == GPIO_INPUT_STATE_RISING_EDGE) {
					program_state = STATE_LED_OFF;
				}
				if (button0_level == GPIO_INPUT_STATE_FALLING_EDGE) {
					program_state = STATE_LED_OFF;
				}
				break;
			default:
				program_state = STATE_LED_OFF;
		}

	}
	
}
