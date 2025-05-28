import os

# hotspot_name = "QVpVMBCE1UiMAsKJV7mR"
# password = "Dn739Irws32eq2I72QxA"
hotspot_name = "raspberry"
password = "raspberry"

os.system(
    f"nmcli device wifi hotspot ssid {hotspot_name} password {password} ifname wlan0"
)
