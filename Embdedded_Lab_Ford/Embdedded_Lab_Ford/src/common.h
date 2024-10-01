#ifndef COMMON_H_
#define COMMON_H_

#define NUM_MICROCONTROLLER_PINS 100

// breadboard LED macros
#define BREADBOARD_LED_PIN EXT1_PIN_6 // Green Wire
#define BREADBOARD_LED_OFF 0
#define BREADBOARD_LED_ON  1

// breadboard button macros
#define BREADBOARD_BUTTON1_PIN EXT1_PIN_7 // Yellow Wire
#define BREADBOARD_BUTTON1_ACIVE true
#define BREADBOARD_BUTTON2_PIN EXT1_PIN_8 // Blue Wire
#define BREADBOARD_BUTTON2_ACIVE true

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

// LCD Backlight
#define LCD_BACKLIGHT_PIN PIN_PC05
typedef enum{
	LCD_BACKLIGHT_OFF = 0,
	LCD_BACKLIGHT_ON = 1
}LCD_BACKLIGHT_TYPE;

// Light Sensor
#define LIGHT_SENSOR_PIN EXT2_PIN_3

// Temperature Unit Enumeration
typedef enum {
	TEMPERATURE_UNIT_CELSIUS = 0,
	TEMPERATURE_UNIT_FAHRENHEIT = 1
} TEMPERATURE_UNIT_TYPE;

#endif /* COMMON_H_ */