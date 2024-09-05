#ifndef COMMON_H_
#define COMMON_H_

// breadboard LED macros
#define BREADBOARD_LED_PIN EXT1_PIN_6
#define BREADBOARD_LED_OFF 0
#define BREADBOARD_LED_ON  1
#define NUM_MICROCONTROLLER_PINS 100

// breadboard button macros
#define BREADBOARD_BUTTON_PIN EXT1_PIN_7
#define BREADBOARD_BUTTON_ACIVE true

// pin level enumeration
// "level" indicates the voltage level of
// the input, either high or low
typedef enum{
	PIN_LEVEL_LOW  = 0,
	PIN_LEVEL_HIGH = 1
}PIN_LEVEL_TYPE;

// gpio input state enumeration
// "state" indicates the state of the input
// when taking the previous level into account
typedef enum{
	GPIO_INPUT_STATE_LOW = 0,			// level is low and was previously low
	GPIO_INPUT_STATE_RISING_EDGE = 1,	// level is high and was previously low
	GPIO_INPUT_STATE_HIGH = 2,			// level is high and was previously high
	GPIO_INPUT_STATE_FALLING_EDGE = 3	// level is low and was previously high
}GPIO_INPUT_STATE_TYPE;

// led state enumeration
// this is a generic term to describe whether the
// LED is on or off, independent of the circuitry
// and whether 0 or 1 turns the LED on
typedef enum{
	LED_STATE_OFF = 0,
	LED_STATE_ON  = 1
}LED_STATE_TYPE;



#endif /* COMMON_H_ */