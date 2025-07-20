#!/usr/bin/python3.11

import time
from datetime import datetime

import paho.mqtt.client as mqtt
import RPi.GPIO as GPIO

# Log process startup (for debugging)
# with open("/home/admin/Desktop/timelog.txt", "a") as f:
#   _datetime = str(datetime.now())
#   f.write(f"Publisher process started at {_datetime}\n")

SERVER_STATE = True

# Setup GPIO pins
GPIO.setmode(GPIO.BOARD)  # Using Board GPIO numbering
INPUT_PIN = 7
READY_LED_PIN = 11
GPIO.setup(INPUT_PIN, GPIO.IN)  # Set our INPUT_PIN as an input pin
GPIO.setup(READY_LED_PIN, GPIO.OUT)  # Set our READY_LED_PIN as an output pin


# Define on_connect event Handler
def on_connect(mosq, obj, rc, d):
    print("Connected to MQTT Broker!")


# Define on_publish event Handler
def on_publish(client, userdata, mid):
    print("Reset message published on device/reset")


def on_message(client, userdata, msg):
    if msg.topic == "device/main":
        global SERVER_STATE
        SERVER_STATE = False
        print("Ready LED off")
    payload = msg.payload.decode()
    print(f"{msg.topic}: {payload}")


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
mqttc.on_message = on_message

# Connect with MQTT Broker
mqttc.connect(MQTT_HOST, MQTT_PORT, MQTT_KEEPALIVE_INTERVAL)

mqttc.subscribe("device/main")

mqttc.loop_start()

while True:
    # Check the server state and toggle the ready led accordingly
    if SERVER_STATE == True:
        GPIO.output(READY_LED_PIN, True)
    else:
        GPIO.output(READY_LED_PIN, False)

    # Check if button is pressed on the board
    if GPIO.input(INPUT_PIN) == True:
        # If pressed, publish reset message to MQTT Topic
        mqttc.publish(MQTT_TOPIC, MQTT_MSG)

        # Toggle server state variable
        SERVER_STATE = True

        time.sleep(2)

    time.sleep(0.1)

# Disconnect from MQTT_Broker
mqttc.loop_stop()
