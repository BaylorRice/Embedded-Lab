/**
 * \file
 *
 * \brief Empty user application template
 *
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
#include "common.h"
#include "utilities.h"

//#define ONE_BUTTON_TWO_LED
#define TWO_BUTTON_TWO_LED
//#define DOUBLE_FLASHLIGHT

int main (void)
{
	board_init();
	#ifdef ONE_BUTTON_TWO_LED
	// configure BREADBOARD_LED_PIN
	ioport_set_pin_dir(BREADBOARD_LED_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(BREADBOARD_LED_PIN, LED_0_INACTIVE);
	
	// configure EXT1_PIN_7
	ioport_set_pin_dir(EXT1_PIN_7, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(EXT1_PIN_7, IOPORT_MODE_PULLDOWN);

	while (1)
	{
		// Is button pressed?
		if (ioport_get_pin_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE)
		{
			// Yes, so turn LED on
			ioport_set_pin_level(LED_0_PIN, LED_0_ACTIVE);

			// Yes, so set EXT1_PIN_6 to same value as LED
			ioport_set_pin_level(BREADBOARD_LED_PIN, BREADBOARD_LED_ON);

		}
		else
		{
			// No, so turn LED off
			ioport_set_pin_level(LED_0_PIN, !LED_0_ACTIVE);

			// Yes, so set EXT1_PIN_6 to same value as LED
			ioport_set_pin_level(BREADBOARD_LED_PIN, BREADBOARD_LED_OFF);
		}
	}
	#endif
	
	#ifdef TWO_BUTTON_TWO_LED
	// configure BREADBOARD_LED_PIN
	ioport_set_pin_dir(BREADBOARD_LED_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(BREADBOARD_LED_PIN, LED_0_INACTIVE);
	
	// configure EXT1_PIN_7
	ioport_set_pin_dir(EXT1_PIN_7, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(EXT1_PIN_7, IOPORT_MODE_PULLDOWN);

	while (1)
	{
		// Is blueboard button pressed?
		if (ioport_get_pin_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE)
		{
			// Yes, so turn LED on
			ioport_set_pin_level(LED_0_PIN, LED_0_ACTIVE);	

		}
		else
		{
			// No, so turn LED off
			ioport_set_pin_level(LED_0_PIN, !LED_0_ACTIVE);

			
		}
		
		// Is breadboard button pressed?
		if (ioport_get_pin_level(BREADBOARD_BUTTON_PIN) == BREADBOARD_BUTTON_ACIVE) {
			
			// Yes, so turn LED on
			ioport_set_pin_level(BREADBOARD_LED_PIN, BREADBOARD_LED_ON);
			
		} else {
			
			// No, so turn LED off
			ioport_set_pin_level(BREADBOARD_LED_PIN, BREADBOARD_LED_OFF);
			
		}
	}
	#endif
	#ifdef DOUBLE_FLASHLIGHT

	#endif
}
