#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "common.h"

// create function prototypes based on the function definitions below
GPIO_INPUT_STATE_TYPE check_gpio_input_state(int);

/////////////////////////////////////////////////////////////////////////////
// Name: check_gpio_input_state
// Inputs: int pin_number - the pin number of the gpio input pin
// Outputs: GPIO_INPUT_STATE_TYPE gpio_input_state
// See definition of GPIO_INPUT_STATE_TYPE in common.h for possible values
// IMPORTANT TERMINOLOGY NOTE: the term "level" simply indicates the 0 or 1
// level of the input pin.  The term "state" is more complex.  It indicates
// the state of the input pin such as FALLING EDGE, LOW, RISING EDGE, or HIGH
// the state takes into account history, whereas level is just a 0 or 1
/////////////////////////////////////////////////////////////////////////////
GPIO_INPUT_STATE_TYPE check_gpio_input_state(int pin_number)
{
	// create static variables for current and previous pin input levels
	// Note on static variables: static variables retain their values even after
	// the function exits because they are stored in the static section of memory
	// rather than the stack.  They are initialized to their initial values the
	// first time the function is called, but then they are not re-initialized
	// each time the function is called
	static PIN_LEVEL_TYPE current_pin_level[NUM_MICROCONTROLLER_PINS];
	static PIN_LEVEL_TYPE prev_pin_level[NUM_MICROCONTROLLER_PINS];
	
	// the following few lines of code are intended to be executed one time to
	// determine the initial state of the pin.  This will prevent incorrectly
	// detecting an edge the first time the code is run
	static bool flags_initialized = false;
	static bool first_time_pin[NUM_MICROCONTROLLER_PINS];
	if(!flags_initialized)
	{
		for(int i=0; i < NUM_MICROCONTROLLER_PINS; i++)
		{
			first_time_pin[i] = true;
		}
		flags_initialized = true;
	}
	if(first_time_pin[pin_number])
	{
		current_pin_level[pin_number] = ioport_get_pin_level(pin_number);
		prev_pin_level[pin_number] = current_pin_level[pin_number];
		first_time_pin[pin_number] = false;
	}
	
	// create and initialize gpio_input_state
	// the initialization value is arbitrary because it will be
	// updated by the logic of the function
	GPIO_INPUT_STATE_TYPE gpio_input_state = GPIO_INPUT_STATE_LOW;
	
	// Save the previous pin level as the current pin level
	prev_pin_level[pin_number] = current_pin_level[pin_number];
	
	// Read GPIO Input Pin Level
	current_pin_level[pin_number] = ioport_get_pin_level(pin_number);
	
	// GPIO Pin Level - IF Low
	if (current_pin_level[pin_number] == PIN_LEVEL_LOW) 
	{
		// Check Previous Pin Level
		// Previous Pin Level - IF Low
		if (prev_pin_level[pin_number] == PIN_LEVEL_LOW) 
		{
			// GPIO Input State = LOW
			gpio_input_state = GPIO_INPUT_STATE_LOW;
			
		// Previous Pin Level - IF High
		}
		else if (prev_pin_level[pin_number] == PIN_LEVEL_HIGH) 
		{
			// GPIO Input State = FALLING_EDGE
			gpio_input_state = GPIO_INPUT_STATE_FALLING_EDGE;
		}
	}
	
	// GPIO Pin Level - IF High
	else if (current_pin_level[pin_number] == PIN_LEVEL_HIGH) 
	{
		// Check Previous Pin Level
		// Previous Pin Level - IF Low
		if (prev_pin_level[pin_number] == PIN_LEVEL_LOW) 
		{
			// GPIO Input State = RISING_EDGE
			gpio_input_state = GPIO_INPUT_STATE_RISING_EDGE;
			
		// Previous Pin Level - IF High
		} 
		else if (prev_pin_level[pin_number] == PIN_LEVEL_HIGH) 
		{
			// GPIO Input State = HIGH
			gpio_input_state = GPIO_INPUT_STATE_HIGH;
		}
	}
	return gpio_input_state;
}

volatile uint32_t ticks = 0;
void SysTick_Handler(){
	ticks++;
	display_stopwatch_time(ticks);
}

#endif /* UTILITIES_H_ */