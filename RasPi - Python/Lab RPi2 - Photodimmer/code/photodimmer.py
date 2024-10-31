# Photodimmer - Lab RPi2 Photodimmer
# Reese Ford
# Created 10/31/2024
# Modified 10/31/2024 by Reese Ford
# Last Commit: e97372023eb7b09bcfdbff7f95a1937e6234c966

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

try:
    # Bunch of Stuff
    pass
except:
    print('Got Keyboard Interrupt. Cleaning up and exiting')
    pwm.set_duty_cycle(0.0)
    GPIO.cleanup()
    sys.exit()
