# ADC Test - Lab RPi2 Photodimmer
# Reese Ford
# Created 10/29/2024
# Modified 10/29/2024 by Reese Ford
# Last Commit: 

# Pin Vars
PIN_SCLK = 23
PIN_MISO = 21
PIN_MOSI = 19
PIN_CS = 24

import spidev

# Initialize SPI
spi = spidev.SpiDev()
spi.open(0, 0)
spi.max_speed_hz = 1000000
