/**
 * Embedded Lab - Atmel
 * Reese Ford
 * Created: Aug 29, 2024
 * Modified: Sept 04, 2024
 * Last Commit: 1de37143a8ad27c89fa7120af5c5186dbfff99b4
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
//#define TWO_BUTTON_TWO_LED
//#define DOUBLE_FLASHLIGHT_REESE
#define DOUBLE_FLASHLIGHT

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
	
	#ifdef DOUBLE_FLASHLIGHT_REESE
	// configure BREADBOARD_LED_PIN
	ioport_set_pin_dir(BREADBOARD_LED_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(BREADBOARD_LED_PIN, LED_0_INACTIVE);
	
	// configure EXT1_PIN_7
	ioport_set_pin_dir(EXT1_PIN_7, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(EXT1_PIN_7, IOPORT_MODE_PULLDOWN);

	// define hold and power variables
	bool board_letgo = true;
	bool bread_letgo = true;
	bool board_led_power = false;
	bool bread_led_power = false;

	while (1)
	{
		// On blueboard button press, toggle led_power
		if (ioport_get_pin_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
			
			// If the button was just pressed, toggle power
			if (board_letgo) {
				board_led_power = !board_led_power;
				
				// Set the check variable to false, telling the program the button was NOT just pressed
				board_letgo = false;
			}
		
		// If the button was let go, change back the check variable
		} else {
			board_letgo = true;
		}
		
		
		// Is board_led_power true?
		if (board_led_power)
		{
			// Yes, so turn LED on
			ioport_set_pin_level(LED_0_PIN, LED_0_ACTIVE);
		}
		else
		{
			// No, so turn LED off
			ioport_set_pin_level(LED_0_PIN, !LED_0_ACTIVE);
		}
		
		// On breadboard button press, toggle led_power
		if (ioport_get_pin_level(BREADBOARD_BUTTON_PIN) == BREADBOARD_BUTTON_ACIVE) {
			
			// If the button was just pressed, toggle power
			if (bread_letgo) {
				bread_led_power = !bread_led_power;
				
				// Set the check variable to false, telling the program the button was NOT just pressed
				bread_letgo = false;
			}
		
		// If the button was let go, change back the check variable
		} else {
			bread_letgo = true;
		}
		
		
		// Is bread_led_power true?
		if (bread_led_power)
		{
			// Yes, so turn LED on
			ioport_set_pin_level(BREADBOARD_LED_PIN, BREADBOARD_LED_ON);
		}
		else
		{
			// No, so turn LED off
			ioport_set_pin_level(BREADBOARD_LED_PIN, BREADBOARD_LED_OFF);
		}
	}

	#endif
	
	#ifdef DOUBLE_FLASHLIGHT
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
}
