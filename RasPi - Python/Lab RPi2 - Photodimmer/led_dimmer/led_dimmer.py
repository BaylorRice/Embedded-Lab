# Last Commit: 0dcaa00832ac12144d83ef8df173f1a5e3257c07

import time
import sys
import os

sys.path.insert(0, 'utilities')
import utilities

pwm = utilities.HW_PWM(2000)

try:
    pwm_value = 0.0
    factor = 1
    while True:
        pwm.set_duty_cycle(pwm_value)
        pwm_value = pwm_value + 0.5*factor
        if pwm_value < 0.0:
            pwm_value = 0.0
            factor = 1
        if pwm_value > 100.0:
            pwm_value = 100.0
            factor = -1
        time.sleep(.01)

except KeyboardInterrupt:
    print('Got Keyboard Interrupt. Cleaning up and exiting')
    pwm.set_duty_cycle(0.0)
    sys.exit()