void setup() {
  pinMode(D1, INPUT);
  pinMode(D2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(D1) == HIGH) {
    Serial.println("button pressed");
    digitalWrite(D2, HIGH);
  } else {
    digitalWrite(D2, LOW);
  }
}
