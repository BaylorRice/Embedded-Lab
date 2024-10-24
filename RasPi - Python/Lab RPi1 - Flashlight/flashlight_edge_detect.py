# Flashlight Edge Detect - Lab RPi1
# Reese Ford
# Created 10/24/2024
# Modified 10/24/2024 by Reese Ford
# Last Commit: f8ec7156e63cbdf60680c6c14e10140279bc5385

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

    # Edge Detect Flashlight
    ledPower = False
    while True:
        channel = GPIO.wait_for_edge(BUTTON_0_PIN, GPIO.RISING, timeout = 1000, bouncetime=10)

        if channel == BUTTON_0_PIN:
            ledPower = not ledPower
        if ledPower:
            GPIO.output(LED_0_PIN, True)
        else:
            GPIO.output(LED_0_PIN, False)

        channel = GPIO.wait_for_edge(BUTTON_0_PIN, GPIO.FALLING, timeout=1000, bouncetime=10)


except KeyboardInterrupt:
    print("Got Keyboard Interrupt. Cleaning up and exiting")
    GPIO.output(LED_0_PIN, False)
    GPIO.cleanup()
    sys.exit()
