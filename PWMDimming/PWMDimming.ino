// PWM调光
const uint8_t POT_PIN = A0;
const uint8_t LED_PIN = 11;

int ADCVal = 0;

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    ADCVal = analogRead(POT_PIN);
    analogWrite(LED_PIN, ADCVal / 4);
    delay(10);
}