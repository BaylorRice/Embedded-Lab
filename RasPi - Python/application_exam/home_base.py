# Home Base - Application Exam 2
# Reese Ford
# Created 11/19/2024
# Modified 11/19/2024 by Reese Ford
# Last Commit: 8e564d4e7d21de80f6de67fc59af24f3f222bc2c

import time
import sys
import paho.mqtt.client as mqtt # type: ignore

sys.path.insert(0, '../utilities')
from utilities import HW_PWM

pwm = HW_PWM(2000)

# Arguments
numArgs = len(sys.argv)
sub_topic_name = sys.argv[1] + '/weather_station/weather_update'

# MQTT Functions
activity = None
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    print('Subscribing to topic ', sub_topic_name)
    client.subscribe(sub_topic_name)

def on_message(client, userdata, msg):
    global activity
    activity = (float(msg.payload))

    if (activity == 0):
        print("Stay home, dude!")
        pwm.set_duty_cycle(0)
    elif (activity == 1):
        print("Bonfire, dude!")
        pwm.set_duty_cycle(25)
    elif (activity == 2):
        print("Surf's up, dude!")
        pwm.set_duty_cycle(50)
    elif (activity == 3):
        print("Too dark to surf, dude!")
        pwm.set_duty_cycle(0)
    elif (activity == 4):
        print("Bag some rays, dude!")
        pwm.set_duty_cycle(100)
    elif (activity == 5):
        print("Too dark to bag rays, dude!")
        pwm.set_duty_cycle(0)
    else:
        print("ERROR: No activity found")
        pwm.set_duty_cycle(0)

# Initialize MQTT
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("broker.emqx.io", 1883, 60)
client.loop_start()

# Print Activity Message
try:
    while True:
        time.sleep(1)

except KeyboardInterrupt:
    print(" Stopping Program")
    sys.exit()