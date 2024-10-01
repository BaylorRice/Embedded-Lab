/**
 * Embedded Lab - Atmel
 * Lab A4 - Digital Thermometer
 * Reese Ford
 * Created: Aug 29, 2024
 * Modified: Oct 01, 2024
 * Last Commit: d87ac312b6e7622e6e6e42bd1c61e9e972f5f1c8
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
	sysclk_init();
	SysTick_Config(sysclk_get_cpu_hz()/1000);
	configure_console();
	c42412a_init();
	eic_setup();
	printf("Initialization Complete\r\n");
	
	// Initialize Temp Sensor
	initialize_temperature_sensor();
	
	uint32_t timestamp = 0;
	while (1) {
		if ((ticks - timestamp) == 200){
			timestamp = ticks;
			read_temp_sensor(temp_unit);
			display_temp(temp_val, temp_unit);
		}
	}
	
}
