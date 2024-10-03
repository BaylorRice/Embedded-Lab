
/*
 * utilities_breadboard.h
 *
 * Created: 10/1/2024 12:17:15 PM
 *  Author: Reese_Ford1
 */ 

#include "common.h"

// Breadboard LED Functions
void configure_bread_led(int pin_num) {
	ioport_set_pin_dir(pin_num, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(pin_num, BREADBOARD_LED_OFF);
}

void set_bread_led(int pin_num, LED_STATE_TYPE level) {
	if (level == LED_STATE_OFF) {
		ioport_set_pin_level(pin_num, BREADBOARD_LED_OFF);
	} else if (level == LED_STATE_ON) {
		ioport_set_pin_level(pin_num, BREADBOARD_LED_ON);
	}
}

// Breadboard Button Functions
void configure_bread_button(int pin_num) {
	ioport_set_pin_dir(pin_num, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(pin_num, IOPORT_MODE_PULLDOWN);
}

GPIO_INPUT_STATE_TYPE read_bread_button(int pin_num) {
	return check_gpio_input_state(pin_num);
}

volatile uint32_t timestamp = 0;
volatile bool button_held = false;
volatile bool trigger = false;

void button_gpio_handler();

void configure_button_interrupt(int pin_number) {
	ioport_set_pin_dir(pin_number, IOPORT_DIR_INPUT);
	gpio_set_pin_callback(pin_number, button_gpio_handler, 1);
	gpio_enable_pin_interrupt(pin_number);
}

