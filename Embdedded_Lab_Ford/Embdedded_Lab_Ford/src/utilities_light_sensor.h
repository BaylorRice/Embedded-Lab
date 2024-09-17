
/*
 * utilities_light_sensor.h
 *
 * Created: 9/17/2024 12:17:42 PM
 *  Author: Reese_Ford1
 */ 

#include "common.h"
#include "utilities.h"

void light_sensor_handler();

void configure_light_sensor() {
	ioport_set_pin_dir(LIGHT_SENSOR_PIN, IOPORT_DIR_INPUT);
	gpio_set_pin_callback(LIGHT_SENSOR_PIN, light_sensor_handler, 1);
	gpio_enable_pin_interrupt(LIGHT_SENSOR_PIN);
	
}

void light_sensor_handler() {
	
}