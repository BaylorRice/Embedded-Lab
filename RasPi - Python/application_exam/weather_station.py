# Weather Station - Application Exam 2
# Reese Ford
# Created 11/19/2024
# Modified 11/19/2024 by Reese Ford
# Last Commit: 

# Pin Vars
PIN_SCLK = 23
PIN_MISO = 21
PIN_MOSI = 19
PIN_CS = 24

import spidev
import time
import sys

# Initialize SPI
spi = spidev.SpiDev()
spi.open(0, 0)
spi.max_speed_hz = 100000

def read_temp_f() :
    # Configure ADC
    configureADCPacket = [0x1, 0x20, 0x0]
    recieved = spi.xfer(configureADCPacket)

    # Convert to ADC Value
    recieved[1] = recieved[1] << 8
    adcValue = recieved[1] + recieved[2]

    # Convert to Voltage
    voltage = (adcValue / (pow(2,10) - 1)) * 3.3
    
    # Convert to Temperature (C)
    temp_c = 100*(voltage) - 50

    # Convert to Temperature (F)
    temp_f = (9/5)*temp_c + 32
    return temp_f

def read_light_voltage() :
    # Configure ADC
    configureADCPacket = [0x1, 0x80, 0x0]
    recieved = spi.xfer(configureADCPacket)

    # Convert to ADC Value
    recieved[1] = recieved[1] << 8
    adcValue = recieved[1] + recieved[2]

    # Convert to Voltage
    voltage = (adcValue / (pow(2,10) - 1)) * 3.3
    return voltage


try: 
    while True:
        voltage = read_light_voltage()
        print(voltage)
        time.sleep(1)
except KeyboardInterrupt:
    print(" Stopping Program")
    sys.exit()