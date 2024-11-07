# Fan Controller Monitor - Lab RPi3 Fan Controller
# Reese Ford
# Created 11/07/2024
# Modified 11/07/2024 by Reese Ford
# Last Commit: 

# Import Modules
import time
import sys
import os

sys.path.insert(0, 'utilities')
import utilities

# Setup PWM
pwm = utilities.HW_PWM(25000)
pwm.set_duty_cycle(100.0)

try:
    # Stuff
    pass

except KeyboardInterrupt:
    print('Got Keyboard Interrupt. Cleaning up and exiting')
    pwm.set_duty_cycle(100.0)
    sys.exit()