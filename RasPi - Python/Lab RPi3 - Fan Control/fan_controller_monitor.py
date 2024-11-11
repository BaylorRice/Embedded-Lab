# Fan Controller Monitor - Lab RPi3 Fan Controller
# Reese Ford
# Created 11/07/2024
# Modified 11/11/2024 by Reese Ford
# Last Commit: 

# Import Modules
import time
import sys
import os

try:
    import RPi.GPIO as GPIO
except RuntimeError:
    print("Error importing RPi.GPIO")

sys.path.insert(0, 'utilities')
import utilities

file = open("rpm_value_file.txt", "w")
file.write("File Start\n")

# Setup PWM
pwm = utilities.HW_PWM(25000)
pwm.set_duty_cycle(100.0)
speedPercent = 0

# Setup GPIO
SENSE_PIN = 16
GPIO.setmode(GPIO.BOARD)
GPIO.setup(SENSE_PIN, GPIO.IN)
current_time = 0
previous_time = 0
rpm_average = 0
count = 0

running_callback = False

def sense_callback(channel):
    running_callback = True
    previous_time = current_time 
    current_time = time.time_ns()

    if (previous_time != 0):
        period = previous_time - current_time
        period = period * pow(10,-9)
        mpr = (period * 2) / 60
        rpm = 1/mpr
        rpm_average += rpm
        count += 1

    if (count == 10):
        count = 0
        rpm_average = rpm_average / 10
        file.write(rpm_average)
        rpm_average = 0

    running_callback = False
        

GPIO.add_event_detect(SENSE_PIN, GPIO.FALLING, bouncetime=10)
GPIO.add_event_callback(SENSE_PIN, sense_callback)

try:
    # Ask user for input
    while True:
        speedPercent = input("Enter desired fan speed as a percentage (0.0 - 100.0): ")
        if (speedPercent > 100):
            speedPercent = 100
        elif (speedPercent < 0):
            speedPercent = 0
        
        pwm.set_duty_cycle(-speedPercent + 100)
    
except KeyboardInterrupt:
    print('Got Keyboard Interrupt. Cleaning up and exiting')
    while running_callback:
        time.sleep(0.1)
    pwm.set_duty_cycle(100.0)
    sys.exit()