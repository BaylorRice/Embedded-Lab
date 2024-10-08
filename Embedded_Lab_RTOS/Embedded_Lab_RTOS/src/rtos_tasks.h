#ifndef RTOS_TASKS_H_
#define RTOS_TASKS_H_

#include <math.h>

#define TIMING_TEST
//#define LOW_SPEED_TEST
//#define HIGH_SPEED_TEST
//#define FULL_TEST
#define TEST_SECONDS 30
#define TEST_HEADING 45

typedef struct buttonInfo {
	GPIO_INPUT_LEVEL_TYPE sw0_level;
	GPIO_INPUT_LEVEL_TYPE sw1_level;
	GPIO_INPUT_LEVEL_TYPE sw2_level;
}ButtonStructType;

ButtonStructType button_info;

typedef struct aircraftData {
	double x_position;
	double y_position;
	double heading;           // heading in degrees from -180 to 180, produced by math functions
	double display_heading;   // heading in degrees from 0-360 based on the -180 to 180 heading
	double speed;
	double latitude;
	double longitude;
	double photo_latitutde;
	double photo_longitude;
}AircraftDataStructType;

void waste_time(int iterations)
{
	static float x = 0.0;
	static float y = 1.0;
	for(int i=0; i < iterations; i++)
		x = x+y;
}

void task_check_buttons(void)
{
	while(1)
	{
		// PART 1 TODO: use vTaskDelayUntil to run this task at 100Hz
		
		#ifdef TIMING_TEST
		ioport_set_pin_level(EXT1_PIN_5, true);
		waste_time(1000);
		ioport_set_pin_level(EXT1_PIN_5, false);
		#endif
	}
}


void task_update_position(void)
{
	const double HIGH_THROTTLE_SPEED = 5000.0;
	const double LOW_THROTTLE_SPEED = 3000.0;
	const double MILES_PER_DEGREE_LAT = 69.0;
	const double MILES_PER_DEGREE_LON = 54.6;
	const double DOVER_LATITUDE = 51.15922;
	const double DOVER_LONGITUDE = 1.202582;
	const uint32_t CYCLES_PER_SECOND = 20;
	
	uint32_t cycle_counter = 0;
	
	while(1)
	{	
		// PART 1 TODO: use vTaskDelayUntil to run this task at 20Hz
				
		#ifdef TIMING_TEST
		ioport_set_pin_level(EXT1_PIN_6, true);
		waste_time(3000);
		ioport_set_pin_level(EXT1_PIN_6, false);
		#endif
		
		#ifdef LOW_SPEED_TEST
		if(cycle_counter > CYCLES_PER_SECOND * TEST_SECONDS)
		{
			printf("Final: %lf, %lf, %lf, %lf\r\n", aircraft_data->speed, aircraft_data->latitude, aircraft_data->longitude, aircraft_data->display_heading);
			break;
		}
		cycle_counter++;
		button_info.sw1_level = GPIO_INPUT_LEVEL_LOW;
		button_info.sw2_level = GPIO_INPUT_LEVEL_LOW;
		aircraft_data->heading = TEST_HEADING;
		#endif
		
		#ifdef HIGH_SPEED_TEST
		if(cycle_counter > CYCLES_PER_SECOND * TEST_SECONDS)
		{
			printf("Final: %lf, %lf, %lf, %lf\r\n", aircraft_data->speed, aircraft_data->latitude, aircraft_data->longitude, aircraft_data->display_heading);
			break;
		}
		cycle_counter++;
		button_info.sw1_level = GPIO_INPUT_LEVEL_HIGH;
		button_info.sw2_level = GPIO_INPUT_LEVEL_HIGH;
		aircraft_data->heading = TEST_HEADING;
		#endif
		
		#ifdef FULL_TEST
		if(cycle_counter < CYCLES_PER_SECOND * 5)
		{
			button_info.sw1_level = GPIO_INPUT_LEVEL_LOW;
			button_info.sw2_level = GPIO_INPUT_LEVEL_LOW;
		}
		else if(cycle_counter < CYCLES_PER_SECOND * 12)
		{
			button_info.sw1_level = GPIO_INPUT_LEVEL_LOW;
			button_info.sw2_level = GPIO_INPUT_LEVEL_HIGH;
		}
		else if(cycle_counter < CYCLES_PER_SECOND * 16)
		{
			button_info.sw1_level = GPIO_INPUT_LEVEL_HIGH;
			button_info.sw2_level = GPIO_INPUT_LEVEL_HIGH;
		}
		else if(cycle_counter < CYCLES_PER_SECOND * 28)
		{
			button_info.sw1_level = GPIO_INPUT_LEVEL_HIGH;
			button_info.sw2_level = GPIO_INPUT_LEVEL_LOW;
		}
		else if(cycle_counter < CYCLES_PER_SECOND * 30)
		{
			button_info.sw1_level = GPIO_INPUT_LEVEL_LOW;
			button_info.sw2_level = GPIO_INPUT_LEVEL_LOW;
		}
		else
		{
			printf("Final: %lf, %lf, %lf, %lf\r\n", aircraft_data->speed, aircraft_data->latitude, aircraft_data->longitude, aircraft_data->display_heading);
			break;
		}
		
		cycle_counter++;
		#endif
		
		// PART 4 TODO: Perform calculations 
		
		// PART 5 TODO: Produce output as specified and take photo
	}
	
	vTaskEndScheduler();
}



#endif /* RTOS_TASKS_H_ */