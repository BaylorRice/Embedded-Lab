# Flashlight Event Detect - Lab RPi1
# Reese Ford
# Created 10/24/2024
# Modified 10/24/2024 by Reese Ford
# Last Commit: none

import time
import sys

try:
    # Pin Vars
    BUTTON_0_PIN = 16
    LED_0_PIN = 18

    # Importing and setting up GPIO
    try:
        import RPi.GPIO as GPIO
    except RuntimeError:
        print("Error importing RPi.GPIO")

    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(BUTTON_0_PIN, GPIO.IN)
    GPIO.setup(LED_0_PIN, GPIO.OUT)
    
    def button_callback(channel):
        print("Entering Callback")
        GPIO.output(LED_0_PIN, True)
        while GPIO.input(BUTTON_0_PIN) == True:
            print("abc")
            time.sleep(0.01)
        GPIO.output(LED_0_PIN, False)
        print("Exiting Callback")

    GPIO.add_event_detect(BUTTON_0_PIN, GPIO.RISING, bouncetime=10)
    GPIO.add_event_callback(BUTTON_0_PIN, button_callback)

    count = 0
    while True:
        time.sleep(1)
        print(count)
        count = count + 1

except KeyboardInterrupt:
    print("Got Keyboard Interrupt. Cleaning up and exiting")
    GPIO.output(LED_0_PIN, False)
    GPIO.cleanup()
    sys.exit()