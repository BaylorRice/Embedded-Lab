#ifndef UTILITIES_LIGHT_SENSOR_H_
#define UTILITIES_LIGHT_SENSOR_H_

#include "utilities_lcd.h"

void light_sensor_handler(void)
{
	set_lcd_backlight(ioport_get_pin_level(LIGHT_SENSOR_PIN));
}

void configure_light_sensor(void)
{
	ioport_set_pin_dir(LIGHT_SENSOR_PIN, IOPORT_DIR_INPUT);
	
	gpio_enable_pin_interrupt (LIGHT_SENSOR_PIN);
	gpio_set_pin_callback (LIGHT_SENSOR_PIN, light_sensor_handler, 7);
	
	set_lcd_backlight(ioport_get_pin_level(LIGHT_SENSOR_PIN));	
}

#endif /* UTILITIES_LIGHT_SENSOR_H_ */