
/*
 * utilities_light_sensor.h
 *
 * Created: 9/17/2024 12:17:42 PM
 *  Author: Reese_Ford1
 */ 

#include "common.h"
#include "utilities.h"

void light_sensor_handler();

// Configure the Light Sensor and the GPIO Interrupt
void configure_light_sensor() {
	ioport_set_pin_dir(LIGHT_SENSOR_PIN, IOPORT_DIR_INPUT);
	gpio_set_pin_callback(LIGHT_SENSOR_PIN, light_sensor_handler, 1);
	gpio_enable_pin_interrupt(LIGHT_SENSOR_PIN);
	
}

/// Light Sensor Interrupt Handler
//		Toggle the LCD Backlight
volatile LCD_BACKLIGHT_TYPE backlight_level = LCD_BACKLIGHT_OFF;
void light_sensor_handler() {
	if (backlight_level == LCD_BACKLIGHT_OFF) {
		backlight_level = LCD_BACKLIGHT_ON;
	} else if (backlight_level == LCD_BACKLIGHT_ON) {
		backlight_level = LCD_BACKLIGHT_OFF;
	}
	
	set_lcd_backlight(backlight_level);
}