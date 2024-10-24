# Flashlight - Lab RPi1
# Reese Ford
# Created 10/24/2024
# Modified 10/24/2024 by Reese Ford
# Last Commit: none

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

while (1):
    if GPIO.input(BUTTON_0_PIN):
        print("Input was HIGH")
    else:
        print("Input was LOW")


