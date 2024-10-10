#ifndef RTOS_TASKS_H_
#define RTOS_TASKS_H_

#include <math.h>

//#define TIMING_TEST
//#define LOW_SPEED_TEST
//#define HIGH_SPEED_TEST
//#define FULL_TEST
//#define TEST_SECONDS 30
//#define TEST_HEADING 45

typedef struct buttonInfo {
	GPIO_INPUT_LEVEL_TYPE sw0_level;
	GPIO_INPUT_LEVEL_TYPE sw1_level;
	GPIO_INPUT_LEVEL_TYPE sw2_level;
}ButtonStructType;

ButtonStructType button_levels;

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
	// Periodic Timing
	TickType_t xLastWakeTime;
	const TickType_t button_check_period = 10;
	xLastWakeTime = xTaskGetTickCount();
	
	while(1)
	{
		// PART 1 DONE: use vTaskDelayUntil to run this task at 100Hz
		vTaskDelayUntil(&xLastWakeTime, button_check_period);
		
		#ifdef TIMING_TEST
		ioport_set_pin_level(EXT1_PIN_5, true);
		waste_time(1000);
		ioport_set_pin_level(EXT1_PIN_5, false);
		#endif
		
		button_levels.sw0_level = ioport_get_pin_level(SW0_PIN);
		button_levels.sw1_level = ioport_get_pin_level(SW1_PIN);
		button_levels.sw2_level = ioport_get_pin_level(SW2_PIN);
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
	const double BERLIN_LATITUDE = 52.5200;
	const double BERLIN_LONGITUDE = 13.4050;
	const uint32_t CYCLES_PER_SECOND = 20;
	
	uint32_t cycle_counter = 0;
	
	AircraftDataStructType *plane_data;
	plane_data = (AircraftDataStructType *) malloc(sizeof(AircraftDataStructType));
	
	plane_data->x_position = DOVER_LONGITUDE * MILES_PER_DEGREE_LON;
	plane_data->y_position = DOVER_LATITUDE * MILES_PER_DEGREE_LAT;
	plane_data->heading = 0;
	plane_data->display_heading = 0;
	plane_data->speed = 0;
	plane_data->latitude = DOVER_LATITUDE;
	plane_data->longitude = DOVER_LONGITUDE;
	plane_data->photo_latitutde = 0;
	plane_data->photo_longitude = 0;
	
	// Periodic Timing
	TickType_t xLastWakeTime;
	const TickType_t position_check_period = 50;
	xLastWakeTime = xTaskGetTickCount();
	
	while(1)
	{	
		// PART 1 DONE: use vTaskDelayUntil to run this task at 20Hz
		vTaskDelayUntil(&xLastWakeTime, position_check_period);
				
		#ifdef TIMING_TEST
		ioport_set_pin_level(EXT1_PIN_6, true);
		waste_time(3000);
		ioport_set_pin_level(EXT1_PIN_6, false);
		#endif
		
		#ifdef LOW_SPEED_TEST
		if(cycle_counter > CYCLES_PER_SECOND * TEST_SECONDS)
		{
			printf("Final: %lf, %lf, %lf, %lf\r\n", plane_data->speed, plane_data->latitude, plane_data->longitude, plane_data->display_heading);
			break;
		}
		cycle_counter++;
		button_levels.sw1_level = GPIO_INPUT_LEVEL_LOW;
		button_levels.sw2_level = GPIO_INPUT_LEVEL_LOW;
		plane_data->display_heading = TEST_HEADING;
		#endif
		
		#ifdef HIGH_SPEED_TEST
		if(cycle_counter > CYCLES_PER_SECOND * TEST_SECONDS)
		{
			printf("Final: %lf, %lf, %lf, %lf\r\n", plane_data->speed, plane_data->latitude, plane_data->longitude, plane_data->display_heading);
			break;
		}
		cycle_counter++;
		button_levels.sw1_level = GPIO_INPUT_LEVEL_HIGH;
		button_levels.sw2_level = GPIO_INPUT_LEVEL_HIGH;
		plane_data->display_heading = TEST_HEADING;
		#endif
		
		#ifdef FULL_TEST
		if(cycle_counter < CYCLES_PER_SECOND * 5) //Both Buttons Unpressed
		{
			button_levels.sw1_level = GPIO_INPUT_LEVEL_LOW;
			button_levels.sw2_level = GPIO_INPUT_LEVEL_LOW;
		}
		else if(cycle_counter < CYCLES_PER_SECOND * 12) //SW2 Pressed, SW1 Unpressed
		{
			button_levels.sw1_level = GPIO_INPUT_LEVEL_LOW;
			button_levels.sw2_level = GPIO_INPUT_LEVEL_HIGH;
		}
		else if(cycle_counter < CYCLES_PER_SECOND * 16) //Both Buttons Pressed
		{
			button_levels.sw1_level = GPIO_INPUT_LEVEL_HIGH;
			button_levels.sw2_level = GPIO_INPUT_LEVEL_HIGH;
		}
		else if(cycle_counter < CYCLES_PER_SECOND * 28) //SW1 Pressed, SW2 Unpressed
		{
			button_levels.sw1_level = GPIO_INPUT_LEVEL_HIGH;
			button_levels.sw2_level = GPIO_INPUT_LEVEL_LOW;
		}
		else if(cycle_counter < CYCLES_PER_SECOND * 30) //Both Buttons Unpressed
		{
			button_levels.sw1_level = GPIO_INPUT_LEVEL_LOW;
			button_levels.sw2_level = GPIO_INPUT_LEVEL_LOW;
		}
		else
		{
			printf("Final: %lf, %lf, %lf, %lf\r\n", plane_data->speed, plane_data->latitude, plane_data->longitude, plane_data->display_heading);
			break;
		}
		
		cycle_counter++;
		#endif
		
		// PART 4 TODO: Perform calculations
		if ((button_levels.sw1_level == GPIO_INPUT_LEVEL_LOW) && (button_levels.sw2_level == GPIO_INPUT_LEVEL_LOW)) {
			plane_data->speed = LOW_THROTTLE_SPEED;
		} 
		else if ((button_levels.sw1_level == GPIO_INPUT_LEVEL_HIGH) && (button_levels.sw2_level == GPIO_INPUT_LEVEL_LOW)) {
			plane_data->speed = LOW_THROTTLE_SPEED;
			plane_data->display_heading += -0.5;
			if (plane_data->display_heading < 0) {
				plane_data->display_heading += 360;
			}
			if (plane_data->display_heading > 360) {
				plane_data->display_heading += -360;
			}
		} 
		else if ((button_levels.sw1_level == GPIO_INPUT_LEVEL_LOW) && (button_levels.sw2_level == GPIO_INPUT_LEVEL_HIGH)) {
			plane_data->speed = LOW_THROTTLE_SPEED;
			plane_data->display_heading += 0.5;
			if (plane_data->display_heading < 0) {
				plane_data->display_heading += 360;
			}
			if (plane_data->display_heading > 360) {
				plane_data->display_heading += -360;
			}
		} 
		else if ((button_levels.sw1_level == GPIO_INPUT_LEVEL_HIGH) && (button_levels.sw2_level == GPIO_INPUT_LEVEL_HIGH)) {
			plane_data->speed = HIGH_THROTTLE_SPEED;
		}
		
		double mps = plane_data->speed / 3600;
		double distance_moved = mps * 0.05;
		double deltaX = distance_moved * cos((plane_data->display_heading * M_PI) / (double)(180));
		double deltaY = distance_moved * sin((plane_data->display_heading * M_PI) / (double)(180));
		plane_data->x_position += deltaX;
		plane_data->y_position += deltaY;
		plane_data->longitude += deltaX / MILES_PER_DEGREE_LON;
		plane_data->latitude += deltaY / MILES_PER_DEGREE_LAT;
		plane_data->heading = plane_data->display_heading - 90;
		
		// PART 5 DONE: Produce output as specified and take photo
		printf("%lf, %lf, %lf, %lf\r\n", plane_data->speed, plane_data->latitude, plane_data->longitude, plane_data->display_heading);
		c42412a_show_numeric_dec((uint32_t)(plane_data->display_heading));
		
		// Update Servo
		double servo_value_d = 3.0;
		uint32_t servo_value_i= 3;
		double servo_angle_cal = plane_data->display_heading;
		
		if ((servo_angle_cal > 90) && (servo_angle_cal < 180)) {
			servo_angle_cal = 90;
		} else if ((servo_angle_cal >=180) && (servo_angle_cal < 270)) {
			servo_angle_cal = -90;
		} else if (servo_angle_cal >= 270) {
			servo_angle_cal = -(360 - servo_angle_cal); 
		}
		servo_value_d = (servo_angle_cal-140.7)/(-18);
		servo_value_i = round(servo_value_d);
		
		change_duty_cycle(servo_value_i);
		//printf("Servo angle Cal: %lf; Servo value (d): %lf; Servo Value: %i\r\n", servo_angle_cal, servo_value_d, servo_value_i);
		
		if (button_levels.sw0_level == GPIO_INPUT_LEVEL_LOW) {
			double distance_from_berlin = 0.0;
			double berlin_x_position = BERLIN_LONGITUDE * MILES_PER_DEGREE_LON;
			double berlin_y_position = BERLIN_LATITUDE * MILES_PER_DEGREE_LAT;
			
			distance_from_berlin = sqrt(pow((berlin_y_position - plane_data->y_position),2) + pow((berlin_x_position - plane_data->x_position),2));
			printf("Final Position: %lf*N %lf*E\r\n", plane_data->latitude, plane_data->longitude);
			printf("Distance to Berlin: %lf\r\n", distance_from_berlin);
			free(plane_data);
			break;
		}
		
	}
	
	vTaskEndScheduler();
}



#endif /* RTOS_TASKS_H_ */