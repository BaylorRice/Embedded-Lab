/**
 * Embedded Lab - Atmel
 * Lab A3 - Event Driven System
 * Reese Ford
 * Created: Aug 29, 2024
 * Modified: Sept 19, 2024
 * Last Commit: 5629f21a641f74a1b46c2d2eba85667cbba007c9
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

// Defining function prototypes so systick can use them
void display_stopwatch_time(uint32_t);
void display_clock_time(uint32_t);

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
	
	c42412a_show_icon(C42412A_ICON_COLON);
}

int main (void)
{
	board_init();
	sysclk_init();
	SysTick_Config(sysclk_get_cpu_hz() / 1000); // One tick = 1ms
	
	// LED0 Delay
	ioport_set_pin_level(LED_0_PIN, LED_0_ACTIVE);
	mdelay(3000);
	ioport_set_pin_level(LED_0_PIN, LED_0_INACTIVE);
	mdelay(3000);
	ioport_set_pin_level(LED_0_PIN, LED_0_ACTIVE);
	
	// Clock
	c42412a_init();
	
	// Backlight Toggle
	configure_lcd_backlight();
	configure_light_sensor();
	if (ioport_get_pin_level(LIGHT_SENSOR_PIN) == 1) {
		backlight_level = LCD_BACKLIGHT_ON;
		set_lcd_backlight(LCD_BACKLIGHT_ON);
	} else {
		backlight_level = LCD_BACKLIGHT_OFF;
		set_lcd_backlight(LCD_BACKLIGHT_OFF);
	}
	
	// Wireless Icon
	eic_setup();
	
	// Breadboard LED Dim
	ioport_set_pin_dir(BREADBOARD_LED_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(BREADBOARD_LED_PIN, BREADBOARD_LED_ON);
	configure_tc();
	
	// Configure Priorities
	NVIC_SetPriority(EIC_1_IRQn, 4);
	NVIC_SetPriority(SysTick_IRQn, 1);
	NVIC_SetPriority(GPIO_0_IRQn, 2);
	NVIC_SetPriority(TC00_IRQn, 3);
	
	uint32_t eic_prio = NVIC_GetPriority(EIC_1_IRQn);
	uint32_t systick_prio = NVIC_GetPriority(SysTick_IRQn);
	uint32_t gpio_prio = NVIC_GetPriority(GPIO_0_IRQn);
	uint32_t tc_prio = NVIC_GetPriority(TC00_IRQn);
	
	
}
