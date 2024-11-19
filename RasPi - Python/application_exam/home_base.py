# Home Base - Application Exam 2
# Reese Ford
# Created 11/19/2024
# Modified 11/19/2024 by Reese Ford
# Last Commit: 

import time
import sys
import paho.mqtt.client as mqtt # type: ignore

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
    elif (activity == 1):
        print("Bonfire, dude!")
    elif (activity == 2):
        print("Surf's up, dude!")
    elif (activity == 3):
        print("Too dark to surf, dude!")
    elif (activity == 4):
        print("Bag some rays, dude!")
    elif (activity == 5):
        print("Too dark to bag rays, dude!")
    else:
        print("ERROR: No activity found")

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