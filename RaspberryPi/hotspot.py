import socket
import network

ssid = "QVpVMBCE1UiMAsKJV7mR"
password = "Dn739Irws32eq2I72QxA"

ap = network.WLAN(network.AP_IF)
ap.config(essid=ssid, password=password)
ap.active(True)

while ap.active == False:
    pass

print("Access point active!")
config = ap.ifconfig()
print(f"IPv4 Address: {config[0]}\nSubnet Mask: {config[1]}\nDefault Gateway: {config[2]}")
