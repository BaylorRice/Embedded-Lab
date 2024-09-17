
/*
 * utilities_lcd.h
 *
 * Created: 9/17/2024 12:04:03 PM
 *  Author: Reese_Ford1
 */ 

#include "common.h"
#include "utilities.h"

// Configre the LCD Backlight
void configure_lcd_backlight() {
	ioport_set_pin_dir(LCD_BACKLIGHT_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LCD_BACKLIGHT_PIN, LCD_BACKLIGHT_OFF);
}

// Set the level of the LCD Backlight
void set_lcd_backlight(LCD_BACKLIGHT_TYPE level) {
	if (level == LCD_BACKLIGHT_ON) {
		ioport_set_pin_level(LCD_BACKLIGHT_PIN, LCD_BACKLIGHT_ON);
	} else if (level == LCD_BACKLIGHT_OFF) {
		ioport_set_pin_level(LCD_BACKLIGHT_PIN, LCD_BACKLIGHT_OFF);
	}
}