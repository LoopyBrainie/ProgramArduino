// 抢答器
const uint8_t RST_BTN_PIN = 2;
const uint8_t GREEN_BTN_PIN = 3;
const uint8_t YELLOW_BTN_PIN = 4;
const uint8_t RED_BTN_PIN = 5;
const uint8_t GREEN_LED_PIN = 6;
const uint8_t YELLOW_LED_PIN = 7;
const uint8_t RED_LED_PIN = 8;

uint8_t RedVal = HIGH;
uint8_t YellowVal = HIGH;
uint8_t GreenVal = HIGH;

void clearLED() {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
}

void redFirst() {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YellowVal, LOW);
    while(digitalRead(RST_BTN_PIN) == HIGH);
    clearLED();
}

void yellowFirst() {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    while(digitalRead(RST_BTN_PIN) == HIGH);
    clearLED();
}

void greenFirst() {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    while(digitalRead(RST_BTN_PIN) == HIGH);
    clearLED();
}

void setup() {
    pinMode(RST_BTN_PIN, INPUT);
    pinMode(RED_BTN_PIN, INPUT);
    pinMode(YELLOW_BTN_PIN, INPUT);
    pinMode(GREEN_BTN_PIN, INPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop() {
    RedVal = digitalRead(RED_BTN_PIN);
    YellowVal = digitalRead(YELLOW_BTN_PIN);
    GreenVal = digitalRead(GREEN_BTN_PIN);


    if (RedVal == LOW) {
        redFirst();
    }
    if (YellowVal == LOW) {
        yellowFirst();
    }
    if (GreenVal == LOW) {
        greenFirst();
    }
}