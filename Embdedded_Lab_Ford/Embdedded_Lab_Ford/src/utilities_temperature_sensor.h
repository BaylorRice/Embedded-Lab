
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
uint8_t set_config_data[2] = {0};
uint8_t set_pointer_temp_reg = 0x00;

// Initialize Temperature Sensor and any TWI functions
status_code_t initialize_temperature_sensor(void) {
	status_code_t write_status = OPERATION_IN_PROGRESS;
	set_config_data[0] = 0x01;
	set_config_data[1] = 0x60;
	
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
	packet_tx.buffer			= (void *) set_config_data;
	packet_tx.length			= LENGTH_TWO_BYTES;
	
	packet_tx.addr[2]			= 0;
	packet_tx.ten_bit			= 0;
	packet_tx.high_speed		= 0;
	packet_tx.high_speed_code	= 0;
	write_status = twi_master_write(TWIM3, &packet_tx);
	
	printf("Temp Sensor Initialized\r\n");
}

// Initialize Temperature Variables
uint8_t read_temp_data[2] = {0};
float temp_val = 0.0;
TEMPERATURE_UNIT_TYPE temp_unit = TEMPERATURE_UNIT_CELSIUS;

// Read the Temp Sensor's Temperature
// Convert the Data into a float temperature (XX.XXX) in the given unit
float read_temp_sensor(TEMPERATURE_UNIT_TYPE tempUnits) {
	// Set pointer register to read temperature
	twi_package_t packet_tx;
	packet_tx.chip				= TEMP_SENSOR_ADDRESS;
	packet_tx.addr[0]			= 0;
	packet_tx.addr[1]			= 0;
	packet_tx.addr_length		= 0;
	packet_tx.buffer			= (void *) &set_pointer_temp_reg;
	packet_tx.length			= LENGTH_ONE_BYTE;
	
	packet_tx.addr[2]			= 0;
	packet_tx.ten_bit			= 0;
	packet_tx.high_speed		= 0;
	packet_tx.high_speed_code	= 0;
	twi_master_write(TWIM3, &packet_tx);
	
	// Read Temperature Data
	twi_package_t packet_rx;
	packet_rx.chip				= TEMP_SENSOR_ADDRESS;
	packet_rx.addr[0]			= 0;
	packet_rx.addr[1]			= 0;
	packet_rx.addr_length		= 0;
	packet_rx.buffer			= (void *) &read_temp_data;
	packet_rx.length			= LENGTH_TWO_BYTES;
	
	packet_rx.addr[2]			= 0;
	packet_rx.ten_bit			= 0;
	packet_rx.high_speed		= 0;
	packet_rx.high_speed_code	= 0;
	twi_master_read(TWIM3, &packet_rx);
	
	// Calculate 
	uint16_t temp_data = (read_temp_data[0] * 0x100) + read_temp_data[1];
	temp_data = temp_data >> 4;
	temp_val = temp_data * 0.0625;
	if (tempUnits == TEMPERATURE_UNIT_FAHRENHEIT) {
		temp_val = (temp_val * 9.0/5.0) + 32;
	}
}