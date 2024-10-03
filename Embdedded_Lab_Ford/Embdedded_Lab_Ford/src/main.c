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
#include <string.h>
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
	c42412a_init();
	sysclk_init();
	SysTick_Config(sysclk_get_cpu_hz()/1000);

	// Configure Breadboard LED
	configure_bread_led(BREADBOARD_LED_PIN);

	// Configure Buttons
	configure_bread_button(BREADBOARD_BUTTON1_PIN);
	configure_bread_button(BREADBOARD_BUTTON2_PIN);
	
	// Define State Machine
	typedef enum {
		IDLE = 0,
		CREATE_CODE = 1,
		SHOW_COMBO = 2,
		LOCKED = 3,
		ENTER_CODE = 4,
		SHOW_DENY = 5,
		SELF_DESTRUCT = 6,
		OPEN = 7
	}FOOTBALL_STATE_TYPE;
	FOOTBALL_STATE_TYPE state = IDLE;
	
	// Define button level variables
	GPIO_INPUT_STATE_TYPE button0_level = GPIO_INPUT_STATE_LOW;
	GPIO_INPUT_STATE_TYPE button1_level = GPIO_INPUT_STATE_LOW;

	// Program Variables
	uint32_t code[4];
	uint32_t input_code[4];
	for (int i = 0; i < 4; i++) {
		code[i] = 0;
		input_code[i] = 0;
	}
	bool code_correct = false;
	uint32_t num_incorrect = 0;
	char code_string[5] = "";
	uint32_t tries = 0;
	uint32_t index = 0;

	while (1)
	{
		button0_level = read_bread_button(BUTTON_0_PIN);
		button1_level = read_bread_button(BREADBOARD_BUTTON1_PIN);
		mdelay(10);
		
		switch(state) {
			case IDLE:
			// Reset all variables
			for (int i = 0; i < 4; i++) {
				code[i] = 0;
				input_code[i] = 0;
			}
			tries = 0;
			
			// Show time
			display_clock_time(ticks);
			
			// IDLE State Change
			if (button0_level == GPIO_INPUT_STATE_FALLING_EDGE) {
				c42412a_clear_all();
				index = 0;
				state = CREATE_CODE;
			}
			break;
			
			case CREATE_CODE:
			if (index < 4) {
				// Set code_string to show code
				for (int i = 0; i < 4; i++) {
					if (code[i] < 10) {
						code_string[i] = code[i] + 48;
					} else {
						code_string[i] = code[i] + 55;
					}
				}
			
				// Show code string
				c42412a_show_text(code_string);
			
				switch(index) {
					case 0: c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_0);
					break;
					case 1: c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_1);
					break;
					case 2: c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_2);
					break;
					case 3: c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_3);
					break;
					default: c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_0);
					break;
				}
				c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_0);
				if (button1_level == GPIO_INPUT_STATE_RISING_EDGE) {
					if (code[index] < 15) {
						code[index] = code[index] + 1;
					} else {
						code[index] = 0;
					}
				}
			
				if (button0_level == GPIO_INPUT_STATE_FALLING_EDGE) {
					index++;
				}
			}
			
			// CREATE_CODE State Change
			if (index == 4) {
				state = SHOW_COMBO;
			}
			
			break;
			
			case SHOW_COMBO:
			// Show Word Combo
			set_bread_led(BREADBOARD_LED_PIN, LED_STATE_ON);
			c42412a_clear_all();
			c42412a_show_text("COMBO");
			mdelay(1000);
			
			// Show Actual Combo
			c42412a_clear_all();
			c42412a_show_text(code_string);
			mdelay(5000);
			c42412a_clear_all();
			for (int i = 0; i<4; i++) {
				code_string[i] = 0;
			}
			state = LOCKED;
			break;
			
			case LOCKED:
			// Show time, reset index
			display_clock_time(ticks);
			index = 0;
			
			// Input Code
			if (button0_level == GPIO_INPUT_STATE_FALLING_EDGE) {
				c42412a_clear_all();
				state = ENTER_CODE;
			}
			break;
			
			case ENTER_CODE:
			if (index < 4) {
				// Set code_string to show input_code
				for (int i = 0; i < 4; i++) {
					if (input_code[i] < 10) {
						code_string[i] = input_code[i] + 48;
						} else {
						code_string[i] = input_code[i] + 55;
					}
				}
				
				// Show code string
				c42412a_show_text(code_string);
				
				switch(index) {
					case 0: c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_0);
					break;
					case 1: c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_1);
					break;
					case 2: c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_2);
					break;
					case 3: c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_3);
					break;
					default: c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_0);
					break;
				}
				c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_0);
				if (button1_level == GPIO_INPUT_STATE_RISING_EDGE) {
					if (input_code[index] < 15) {
						input_code[index] = input_code[index] + 1;
						} else {
						input_code[index] = 0;
					}
				}
				
				if (button0_level == GPIO_INPUT_STATE_FALLING_EDGE) {
					index++;
				}
			}
			
			// Check Code
			if (index == 4) {
				code_correct = true;
				for (int i = 0; i<4; i++) {
					if (code_correct) {
						if (code[i] != input_code[i]) {
							code_correct = false;
						}
					}
				}
				if (code_correct) {
					state = OPEN;
					} else if (!code_correct) {
					if (num_incorrect == 0) {
						num_incorrect = 1;
						uint32_t timestamp = ticks;
						state = SHOW_DENY;
						} else if (num_incorrect == 1) {
						num_incorrect = 2;
						state = SELF_DESTRUCT;
					}
				}
			}
			break;
			
			case SHOW_DENY:
			// SHOW_DENY Action
			c42412a_clear_all();
			c42412a_show_text("DENY");
			
			// Toggle LED
			set_bread_led(LED_0_PIN, LED_0_ACTIVE);
			mdelay(1000);
			set_bread_led(LED_0_PIN, LED_0_INACTIVE);
			mdelay(1000);
			set_bread_led(LED_0_PIN, LED_0_ACTIVE);
			mdelay(1000);
			set_bread_led(LED_0_PIN, LED_0_INACTIVE);
			mdelay(1000);
			set_bread_led(LED_0_PIN, LED_0_ACTIVE);
			mdelay(1000);
			
			// SHOW_DENY State Change
			c42412a_clear_all();
			index = 0;
			for (int i = 0; i<4; i++) {
				input_code[i] = 0;
			}
			state = LOCKED;
			break;
			
			case SELF_DESTRUCT:
			// SELF_DESTRUCT Action
			c42412a_clear_all();
			
			exit(0);
			break;
			
			case OPEN:
			// OPEN Action
			
			// OPEN State Change
			break;
			
			default:
			state = IDLE;
			
		}
	}
	
}
