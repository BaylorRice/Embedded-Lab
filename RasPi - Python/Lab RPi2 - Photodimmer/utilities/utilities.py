# Last Commit: 0dcaa00832ac12144d83ef8df173f1a5e3257c07

import time
import sys
import os

PWM_PATH = "/sys/class/pwm/pwmchip0"

class HW_PWM:
    def __init__(self, frequency):
        self.frequency = frequency 
        self.period = int(1000000000 / frequency)
        self.duty_cycle_percent = 0
        self.duty_cycle = 0
        export_cmd = "echo 0 > " + PWM_PATH + "/export"
        enable_cmd = "echo 1 > " + PWM_PATH + "/pwm0/enable"

        print('HW_PWM - Create PWM0')
        print('HW_PWM - ' + export_cmd)
        os.system(export_cmd)
        time.sleep(0.5)

        print('HW_PWM - Set the period')
        period_cmd = "echo " + str(self.period) + " > " + PWM_PATH + "/pwm0/period"
        print(period_cmd)
        os.system(period_cmd)
        time.sleep(0.5)

        print('HW_PWM - Set duty cycle to 0')
        duty_cycle_cmd = "echo 0 > " + PWM_PATH + "/pwm0/duty_cycle"
        print(duty_cycle_cmd)
        os.system(duty_cycle_cmd)
        time.sleep(0.5)

        print('HW_PWM - Enable PWM0')
        print('HW_PWM - ' + enable_cmd)
        os.system(enable_cmd)
        time.sleep(0.5)

    def set_duty_cycle(self, duty_cycle_percent):
        if duty_cycle_percent > 100:
            duty_cycle_percent = 100
        elif duty_cycle_percent < 0:
            duty_cycle_percent = 0    

        self.duty_cycle_int = self.period * duty_cycle_percent/100
        duty_cycle_cmd = "echo " + str(int(self.duty_cycle_int)) + " > " + PWM_PATH + "/pwm0/duty_cycle"
        
        print("HW_PWM - Set duty cycle to " + str(self.duty_cycle_int) + " (" + str(duty_cycle_percent) + "%)")
        print("HW_PWM - " + duty_cycle_cmd)
        os.system(duty_cycle_cmd)
        time.sleep(0.01)