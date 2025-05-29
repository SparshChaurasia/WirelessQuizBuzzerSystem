# Wireless Quiz Buzzer System with Raspberry Pi 3B+ and ESP8266 (Wemos D1 Mini)
<center>A wireless quiz buzzer system using Raspberry Pi as game master and ESP8266 as buzzers.</center>

## System Achitecture
![Pub Sub Client Model](./assets/system_architecture.png)

## Server Setup (Raspberry Pi 3B+)
### Install Mosquitto MQTT Broker on Raspberry Pi
1. Update your OS
```
sudo apt update && sudo apt upgrade
```
2. Install Package
```
sudo apt-get install mosquitto mosquitto-clients
```
3. To run MQTT broker on startup
```
sudo systemctl enable mosquitto.service
```
4. Check version and installation details
```
mosquitto -v
```
### Enable Remote Access
This allows clients from other than local device to publish / subscibe to the MQTT broker.
1. Open configuration file
```
sudo nano /etc/mosquitto/mosquitto.conf
```
2. Paste the following lines in the end
```
listener 1883
allow_anonymous true
```
3. Restart the broker
```
sudo systemctl restart mosquitto
```
4. Check status
```
sudo systemctl status mosquitto
```
### Get IP
```
hostname -I
```
### Test MQTT Server
1. Subscribe to a topic
```
mosquitto_sub -d -t "MyTopic"
```
2. Publish message from another client (terminal)
```
mosquitto_pub -d -t "MyTopic" -m "Hello"
```