#!/usr/bin/python3.11

import time
from datetime import datetime

import paho.mqtt.client as mqtt
import RPi.GPIO as GPIO

# Log process startup
with open("/home/admin/Desktop/timelog.txt", "a") as f:
    _datetime = str(datetime.now())
    f.write(f"Publisher process started at {_datetime}\n")

# Setup GPIO pins
GPIO.setmode(GPIO.BOARD)  # Set's GPIO pins to BCM GPIO numbering
INPUT_PIN = 7  # Sets our input pin
GPIO.setup(INPUT_PIN, GPIO.IN)  # Set our input_pin to be an input


# Define on_connect event Handler
def on_connect(mosq, obj, rc):
    print("Connected to MQTT Broker!")


# Define on_publish event Handler
def on_publish(client, userdata, mid):
    print("Reset message published on device/reset")


# Setup MQTT client
MQTT_HOST = "10.42.0.1"
MQTT_PORT = 1883
MQTT_KEEPALIVE_INTERVAL = 5
MQTT_TOPIC = "device/reset"
MQTT_MSG = "1"

# Initiate MQTT Client
mqttc = mqtt.Client()

# Register Event Handlers
mqttc.on_publish = on_publish
mqttc.on_connect = on_connect

# Connect with MQTT Broker
mqttc.connect(MQTT_HOST, MQTT_PORT, MQTT_KEEPALIVE_INTERVAL)


while True:
    # Check if button is pressed on the board
    if GPIO.input(INPUT_PIN) == True:
        # If pressed, publish reset message to MQTT Topic
        mqttc.publish(MQTT_TOPIC, MQTT_MSG)
        time.sleep(2)

    time.sleep(0.1)

# Disconnect from MQTT_Broker
mqttc.disconnect()
