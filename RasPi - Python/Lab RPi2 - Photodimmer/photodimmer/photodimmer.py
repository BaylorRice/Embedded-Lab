# Photodimmer - Lab RPi2 Photodimmer
# Reese Ford
# Created 10/31/2024
# Modified 10/31/2024 by Reese Ford
# Last Commit: 0dcaa00832ac12144d83ef8df173f1a5e3257c07

# Pin Vars
PIN_SCLK = 23
PIN_MISO = 21
PIN_MOSI = 19
PIN_CS = 24

BUTTON_0_PIN = 16

# Module Imports
import spidev
import time
import sys
import os

sys.path.insert(0, 'utilities')
from utilities import HW_PWM

try:
    import RPi.GPIO as GPIO
except RuntimeError:
    print("Error importing RPi.GPIO")

# Setup
GPIO.setmode(GPIO.BOARD)
GPIO.setup(BUTTON_0_PIN, GPIO.IN)

pwm = HW_PWM(2000)

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

    return adcValue

try:
    # Calibration - Covered (max)
    print(" ")
    print("Cover the photosensor and press the push button")
    while True:
        channel = GPIO.wait_for_edge(BUTTON_0_PIN, GPIO.RISING, timeout = 1000, bouncetime=10)
        if channel == BUTTON_0_PIN:
            max_adcValue = read_adc()

            channel = GPIO.wait_for_edge(BUTTON_0_PIN, GPIO.FALLING, timeout=1000, bouncetime=10)
            break

    # Calibration - Bright (min)
    print("Shine a flashlight on the photosensor and press the push button")
    while True:
        channel = GPIO.wait_for_edge(BUTTON_0_PIN, GPIO.RISING, timeout = 1000, bouncetime=10)
        if channel == BUTTON_0_PIN:
            min_adcValue = read_adc()

            channel = GPIO.wait_for_edge(BUTTON_0_PIN, GPIO.FALLING, timeout=1000, bouncetime=10)
            break
    
    print("Max:", max_adcValue, "  Min:", min_adcValue)

    m = (0 - 100) / (min_adcValue - max_adcValue)

    # Photodimmer
    while True:
        adcValue = read_adc()
        print(adcValue)
        dutyCycleVal = m * (adcValue - min_adcValue)
        print(dutyCycleVal)
        pwm.set_duty_cycle(dutyCycleVal)


except KeyboardInterrupt:
    print('Got Keyboard Interrupt. Cleaning up and exiting')
    pwm.set_duty_cycle(0.0)
    GPIO.cleanup()
    sys.exit()
