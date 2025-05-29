print("Publisher is running...")
input()
"""
import paho.mqtt.client as mqtt

MQTT_HOST = "10.42.0.1"
MQTT_PORT = 1883
MQTT_KEEPALIVE_INTERVAL = 5
MQTT_TOPIC = "device/reset"
MQTT_MSG = "1"

# Define on_connect event Handler
def on_connect(mosq, obj, rc):
    print("Connected to MQTT Broker!")


# Define on_publish event Handler
def on_publish(client, userdata, mid):
    print("Reset message published on device/reset")


# Initiate MQTT Client
mqttc = mqtt.Client()

# Register Event Handlers
mqttc.on_publish = on_publish
mqttc.on_connect = on_connect

# Connect with MQTT Broker
mqttc.connect(MQTT_HOST, MQTT_PORT, MQTT_KEEPALIVE_INTERVAL)

while True:
    # Check if button is pressed on the board

    # If pressed, publish message to MQTT Topic
    # mqttc.publish(MQTT_TOPIC, MQTT_MSG)

# Disconnect from MQTT_Broker
mqttc.disconnect()
"""
