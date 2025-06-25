// Code to test circuit and verify connections 

const int LED_PIN = D5;
const int BUZZER_PIN = D6;
const int DELAY_TIME = 500;


void setup() {
  pinMode(D1, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  // Serial.begin(9600);
}


void loop() {
  // delay(10);
  if (digitalRead(D1) == HIGH) {
    // Serial.println("button not pressed");
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
  } else {
    // Serial.println("button pressed");
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
}
