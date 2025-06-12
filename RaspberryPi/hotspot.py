#!/usr/bin/python3.11

import os
from datetime import datetime

with open("/home/admin/Desktop/timelog.txt", "a") as f:
    _datetime = str(datetime.now())
    f.write(f"Hotspot process started at {_datetime}\n")

# hotspot_name = "QVpVMBCE1UiMAsKJV7mR"
# password = "Dn739Irws32eq2I72QxA"
hotspot_name = "raspberry"
password = "raspberry"

os.system(
    f"nmcli device wifi hotspot ssid {hotspot_name} password {password} ifname wlan0"
)
