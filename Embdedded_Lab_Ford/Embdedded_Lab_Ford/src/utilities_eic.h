/*
 * utilities_eic.h
 *
 * Created: 9/17/2024 12:38:56 PM
 *  Author: Reese_Ford1
 */ 

#include "common.h"
#include "utilities.h"

/// SW0 Interrupt Handler
//		Turn on Wireless signal icon
//		Once the button is let go, turn it off
void eic_callback() {
	if (eic_line_interrupt_is_pending(EIC, GPIO_PUSH_BUTTON_EIC_LINE)) {
		eic_line_clear_interrupt(EIC, GPIO_PUSH_BUTTON_EIC_LINE);
	}
	
	if (temp_unit == TEMPERATURE_UNIT_FAHRENHEIT) {
		temp_unit = TEMPERATURE_UNIT_CELSIUS;
	} else if (temp_unit == TEMPERATURE_UNIT_CELSIUS) {
		temp_unit = TEMPERATURE_UNIT_FAHRENHEIT;
	}
	
}

// Configure the SW0 button EIC Interrupt
void eic_setup() {
	eic_enable(EIC);
	
	struct eic_line_config eic_line_conf;
	eic_line_conf.eic_mode = EIC_MODE_EDGE_TRIGGERED;
	eic_line_conf.eic_edge = EIC_EDGE_FALLING_EDGE;
	eic_line_conf.eic_level = EIC_LEVEL_LOW_LEVEL;
	eic_line_conf.eic_filter = EIC_FILTER_DISABLED;
	eic_line_conf.eic_async = EIC_ASYNCH_MODE;
	
	eic_line_set_config(EIC, GPIO_PUSH_BUTTON_EIC_LINE, &eic_line_conf);
	
	eic_line_set_callback(EIC, GPIO_PUSH_BUTTON_EIC_LINE, eic_callback,
	GPIO_PUSH_BUTTON_EIC_IRQ, 1);
	
	eic_line_enable(EIC, GPIO_PUSH_BUTTON_EIC_LINE);
	
	c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_0);
}