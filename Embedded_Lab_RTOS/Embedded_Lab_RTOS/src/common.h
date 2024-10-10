#ifndef COMMON_H_
#define COMMON_H_

#define BREADBOARD_LED_PIN EXT1_PIN_6
#define BREADBOARD_LED_OFF 0
#define BREADBOARD_LED_ON  1
#define BREADBOARD_BUTTON_PIN EXT1_PIN_7
#define SW1_PIN BREADBOARD_BUTTON_PIN
#define SW2_PIN EXT1_PIN_8
#define NUM_MICROCONTROLLER_PINS 100


// gpio input level enumeration
// "level" indicates the current level of the input,
// either high or low
typedef enum{
	GPIO_INPUT_LEVEL_LOW  = 0,
	GPIO_INPUT_LEVEL_HIGH = 1
}GPIO_INPUT_LEVEL_TYPE;

// gpio input state enumeration
// "state" indicates the state of the button
// when taking the previous state into account
typedef enum{
	GPIO_INPUT_STATE_LOW = 0,
	GPIO_INPUT_STATE_RISING_EDGE = 1,
	GPIO_INPUT_STATE_HIGH = 2,
	GPIO_INPUT_STATE_FALLING_EDGE = 3
}GPIO_INPUT_STATE_TYPE;

// led state enumeration
typedef enum{
	LED_STATE_OFF = 0,
	LED_STATE_ON  = 1
}LED_STATE_TYPE;

#endif /* COMMON_H_ */