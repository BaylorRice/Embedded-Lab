# Flashlight - Lab RPi1
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

    # Basic Flashlight
    letgo = True
    led_power = False

    while True:
        if GPIO.input(BUTTON_0_PIN):
            if letgo:
                led_power = not led_power
                letgo = False

        else:
            letgo = True

        if led_power:
            GPIO.output(LED_0_PIN, True)
        else:
            GPIO.output(LED_0_PIN, False)

        time.sleep(0.01)

except KeyboardInterrupt:
    print("Got Keyboard Interrupt. Cleaning up and exiting")
    GPIO.output(LED_0_PIN, False)
    GPIO.cleanup()
    sys.exit()