// 按键控制LED灯
const uint8_t LED_PIN = 10;
const uint8_t BTN_PIN = 7;

uint8_t BTNVal = LOW;
uint8_t BTNValLast = LOW;
uint8_t LEDState = LOW;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BTN_PIN, INPUT);   
}

void loop() {
    BTNVal = digitalRead(BTN_PIN);

    if (BTNValLast == LOW && BTNVal == HIGH) {
        LEDState = !LEDState;
        delay(10);
        }

    BTNValLast = BTNVal;
    digitalWrite(LED_PIN, LEDState);
}