const uint8_t LED_BASE_PIN = 2;
const uint8_t LED_NUM = 6;

void setup() {
    for (uint8_t i = LED_BASE_PIN; i < LED_BASE_PIN + LED_NUM; i++) {
        pinMode(i, OUTPUT);
    }
}

void loop() {
    for (uint8_t i = LED_BASE_PIN; i < LED_BASE_PIN + LED_NUM; i++) {
        digitalWrite(i, HIGH); 
        delay(1000);
    }
    for (uint8_t i = LED_BASE_PIN; i < LED_BASE_PIN + LED_NUM; i++) {
        digitalWrite(i, LOW); 
        delay(1000);
    }
}