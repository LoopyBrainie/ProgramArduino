const uint8_t LED_PIN = 13;

int ReadVal;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  ReadVal = Serial.read();
  if (ReadVal == 'R') {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
    Serial.println("Hello World!");
  }
}