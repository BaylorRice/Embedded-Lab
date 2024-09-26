
/*
 * utilities_temperature_sensor.h
 *
 * Created: 9/24/2024 1:14:52 PM
 *  Author: Reese_Ford1
 */ 

#define TEMP_SENSOR_ADDRESS 0x4F;
#define LENGTH_THREE_BYTES 3
#define LENGTH_TWO_BYTES 2
#define LENGTH_ONE_BYTE 1

// Transmit Buffers
uint16_t set_config_data = 0x6001;

// Initialize Temperature Sensor and any TWI functions
status_code_t initialize_temperature_sensor(void) {
	status_code_t write_status = OPERATION_IN_PROGRESS;
	// Set TWIM Configuration
	struct twim_config twim_conf;
	twim_conf.twim_clk						= sysclk_get_cpu_hz();
	twim_conf.speed							= TWI_STD_MODE_SPEED;
	twim_conf.smbus							= false;
	twim_conf.hsmode_speed					= 0;
	twim_conf.data_setup_cycles				= 0;
	twim_conf.hsmode_data_setup_cycles		= 0;

	twim_conf.clock_slew_limit				= 0;
	twim_conf.clock_drive_strength_low		= 0;
	twim_conf.data_slew_limit				= 0;
	twim_conf.data_drive_strength_low		= 0;
	twim_conf.hs_clock_slew_limit			= 0;
	twim_conf.hs_clock_drive_strength_high	= 0;
	twim_conf.hs_clock_drive_strength_low	= 0;
	twim_conf.hs_data_slew_limit			= 0;
	twim_conf.hs_data_drive_strength_low	= 0;
	twim_set_config(TWIM3, &twim_conf);
	twim_set_callback(TWIM3, 0, twim_default_callback, 1);
	
	// Configure and send configuration packet
	twi_package_t packet_tx;
	packet_tx.chip				= TEMP_SENSOR_ADDRESS;
	packet_tx.addr[0]			= 0;
	packet_tx.addr[1]			= 0;
	packet_tx.addr_length		= 0;
	packet_tx.buffer			= (void *) &set_config_data;
	packet_tx.length			= LENGTH_TWO_BYTES;
	
	packet_tx.addr[2]			= 0;
	packet_tx.ten_bit			= 0;
	packet_tx.high_speed		= 0;
	packet_tx.high_speed_code	= 0;
	write_status = twi_master_write(TWIM3, &packet_tx);
	
	printf("Temp Sensor Initialized\r\n");
}

// Initialize Temperature Variables
float temp_val = 0.0;
TEMPERATURE_UNIT_TYPE temp_unit = TEMPERATURE_UNIT_CELSIUS;

// Read the Temp Sensor's Temperature
// Convert the Data into a float temperature (XX.XXX) in the given unit
float read_temp_sensor(TEMPERATURE_UNIT_TYPE tempUnits) {
	// TODO: This function
}