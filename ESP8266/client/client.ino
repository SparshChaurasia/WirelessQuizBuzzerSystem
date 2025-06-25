#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const int LED_PIN = D5;
const int BUZZER_PIN = D6;
const int DELAY_TIME = 500;

// const char* ssid = "QVpVMBCE1UiMAsKJV7mR";
// const char* password = "Dn739Irws32eq2I72QxA";
const char ssid[] = "raspberry";  // For Debugging purposes
const char password[] = "raspberry";  // For Debugging purposes
const char mqtt_server[] = "10.42.0.1";
const char device_id[] = "1";

bool is_listening = true;

WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {
  // Connect to Raspberry's Wifi network

  delay(10);
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
  Serial.println("WiFi connected successfully!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Function to handle on message event

  Serial.print("[");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((String)topic == "device/main" && is_listening == true) {
    if ((char)payload[0] == device_id[0]) {
      // Button was pressed by this device

      // Logs for debug
      Serial.print("Button press from device id ");
      Serial.print((char)payload[0]);
      Serial.println(" was registered");
      Serial.println("(LED lights up and buzzer is Sounded)");

      // Update listening state
      is_listening = false;

      // Set LED and buzzer pin high for a moment 
      digitalWrite(LED_PIN, HIGH);
      tone(BUZZER_PIN, 400); // A4
      delay(DELAY_TIME);
      tone(BUZZER_PIN, 500); // B4
      delay(DELAY_TIME);
      tone(BUZZER_PIN, 550); // C4
      delay(DELAY_TIME);
      tone(BUZZER_PIN, 600); // D4
      delay(DELAY_TIME);
      tone(BUZZER_PIN, 650); // E4
      delay(DELAY_TIME);
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);

    } else {
      // Button was pressed by some other device

      // Logs for debug
      Serial.print("Button press from device id ");
      Serial.print((char)payload[0]);
      Serial.println(" was registered");
      Serial.println("Stopped listening to updates on the device/main channel");

      // Update listening state
      is_listening = false;

      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);

    }
  } else if ((String)topic == "device/reset") {
    if ((char)payload[0] == '1') {
      // If reset message is recieved on the device/reset topic to start listening

      // Log for debug  
      Serial.println("Started listening to updates on the device/main channel");

      // Update listening state
      is_listening = true;

      // Turn on led and buzzer for a brief moment to show that the device is reset
      digitalWrite(LED_PIN, HIGH);
      tone(BUZZER_PIN, 650); // A4
      delay(DELAY_TIME);      
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
    }
  }

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
      Serial.println("Connected to MQTT broker!");
      // Once connected subscribe to the topics
      client.subscribe("device/main");
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
  // Setup pins according to the circuit
  pinMode(D1, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // MQTT client and WiFi setup
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
  
  // Check if button is pressed
  if (digitalRead(D1) == HIGH) {
    // Log for debug
    Serial.println("Published device id to device/main");

    // Publish message to MQTT broker
    client.publish("device/main", device_id);
    delay(1000);
  }
}

