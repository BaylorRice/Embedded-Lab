# ADC Test - Lab RPi2 Photodimmer
# Reese Ford
# Created 10/29/2024
# Modified 10/31/2024 by Reese Ford
# Last Commit: f8cca12ffa04efa37e831f708b6f7b54d4254ce0

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

def read_adc() :
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
        voltage = read_adc()
        print(voltage)
        time.sleep(1)
except KeyboardInterrupt:
    print(" Stopping Program")
    sys.exit()