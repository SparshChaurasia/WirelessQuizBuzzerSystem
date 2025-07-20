#!/usr/bin/python3.11

import time
from datetime import datetime

import paho.mqtt.client as mqtt


# Define on_connect event Handler
def on_connect(mosq, obj, rc, d):
    print("Connected to MQTT Broker!")


# Define on_publish event Handler
def on_publish(client, userdata, mid):
    print("Reset message published on device/reset")


def on_message(client, userdata, msg):
    if msg.topic == "device/main":
        print("led off")
    payload = msg.payload.decode()
    print(f"{msg.topic}: {payload}")


# Setup MQTT client
MQTT_HOST = "10.42.0.1"
MQTT_PORT = 1883
MQTT_KEEPALIVE_INTERVAL = 5


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
    try:
        mqttc.publish("device/main", "Hi")
        time.sleep(3)
    except:
        print("Disconnected")
        break

mqttc.loop_stop()
