# MQTT Fan App - Lab RPi4 MQTT
# Reese Ford
# Created 11/12/2024
# Modified 11/12/2024 by Reese Ford
# Last Commit: 7af853b572ecc58dcb683da42b82bdc675b2d346

# Import Modules
import time
import sys
import os
import paho.mqtt.client as mqtt

try:
    import RPi.GPIO as GPIO
except RuntimeError:
    print("Error importing RPi.GPIO")

sys.path.insert(0, '../utilities')
import utilities

# Arguments
numArgs = len(sys.argv)
my_name = sys.argv[1]
partner_name = sys.argv[2]
pub_topic_name = my_name + '/mqtt_fan/fan_rpm_value'
sub_topic_name = partner_name + '/command_center/desired_speed'

# MQTT Functions
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    print('Subscribing to topic ', sub_topic_name)
    client.subscribe(sub_topic_name)

desired_speed = 0
def on_message(client, userdata, msg):
    global desired_speed
    desired_speed = (float(msg.payload))

# Initialize MQTT
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("broker.emqx.io", 1883, 60)
client.loop_start()

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

# Sense Interrupt
def sense_callback(channel):
    global running_callback 
    global previous_time
    global current_time
    global count
    global rpm_average

    running_callback = True
    previous_time = current_time 
    current_time = time.time_ns()

    if (previous_time != 0):
        period = current_time - previous_time
        period = period * pow(10,-9)
        mpr = (period * 2) / 60
        rpm = 1/mpr
        rpm_average += rpm
        count += 1

    if (count == 10):
        count = 0
        rpm_average = rpm_average / 10
        client.publish(pub_topic_name, payload=rpm_average, qos=0, retain=False)
        rpm_average = 0

    running_callback = False
        
# Set GPIO Interrupts
GPIO.add_event_detect(SENSE_PIN, GPIO.FALLING, bouncetime=10)
GPIO.add_event_callback(SENSE_PIN, sense_callback)

try:
    # Ask user for input
    while True:
        pwm.set_duty_cycle(-desired_speed + 100)
    
except KeyboardInterrupt:
    print('Got Keyboard Interrupt. Cleaning up and exiting')
    while running_callback:
        time.sleep(0.1)
    pwm.set_duty_cycle(100.0)
    sys.exit()