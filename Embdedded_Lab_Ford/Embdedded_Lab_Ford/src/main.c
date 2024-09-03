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

#define ONE_BUTTON_TWO_LED
//#define TWO_BUTTON_TWO_LED
//#define DOUBLE_FLASHLIGHT

int main (void)
{
	board_init();
	#ifdef ONE_BUTTON_TWO_LED
	// configure BREADBOARD_LED_PIN
	ioport_set_pin_dir(BREADBOARD_LED_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(BREADBOARD_LED_PIN, LED_0_INACTIVE);

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

	#endif
	#ifdef DOUBLE_FLASHLIGHT

	#endif
}
