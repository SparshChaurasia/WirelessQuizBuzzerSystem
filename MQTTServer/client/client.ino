#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Raspberry Pi Wifi name and password goes here
const char* ssid = "........";
const char* password = "........";
// Local Ip of Raspberry Pi goes here
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
//unsigned long lastMsg = 0;
//#define MSG_BUFFER_SIZE	(50)
//char msg[MSG_BUFFER_SIZE];
int value = 0;
int listening = 1;
int device_id = 1;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  /* Our main logic for switching on the circuit or unsubscribing goes here */
  if (topic == "device/reset") {
    listening = 1;
    Serial.println("Device reset for another buzzer round...");
  } else if (topic == "device/main" && listening == 1) {
    if (int)payload[i] == device_id {
        // light the led and sound the buzzer a few times
        listening = 0;
    } else if {
      listening = 0;
    }
  };

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("device/reset");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // check for button press
  if (true) {
    
    Serial.print("Publish message: ");
    Serial.println(device_id);
    client.publish("device/main", device_id);
  }
}
