/*
 * utilities_eic.h
 *
 * Created: 9/17/2024 12:38:56 PM
 *  Author: Reese_Ford1
 */ 

#include "common.h"
#include "utilities.h"

void eic_callback() {
	if (eic_line_interrupt_is_pending(EIC, GPIO_PUSH_BUTTON_EIC_LINE)) {
		eic_line_clear_interrupt(EIC, GPIO_PUSH_BUTTON_EIC_LINE);
	}
	
	while (ioport_get_pin_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
		c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_1);
		c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_2);
		c42412a_show_icon(C42412A_ICON_WLESS_LEVEL_3);
	}
	
	c42412a_clear_icon(C42412A_ICON_WLESS_LEVEL_1);
	c42412a_clear_icon(C42412A_ICON_WLESS_LEVEL_2);
	c42412a_clear_icon(C42412A_ICON_WLESS_LEVEL_3);
}

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