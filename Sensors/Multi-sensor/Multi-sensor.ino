const uint8_t sensorCount = 2; // 传感器数量
const uint8_t lightSensorPin = 2;
const uint8_t ledPin = 13; 
const uint8_t pirSensorPin = 3; // 人体传感器（数字口）
const uint8_t soundSensorPin = A0; // 声音传感器（模拟口）
const int soundThreshold = 46; // 声音阈值

int lightSensorState = 0; // 初始化光敏传感器状态
int pirSensorState = 0; // 人体传感器状态
int soundSensorValue = 0; // 声音传感器原始值
int soundSensorState = 0; // 声音传感器是否超过阈值

unsigned long triggerWindowStart = 0; // 触发窗口起始时间
const unsigned long triggerWindowDuration = 5000; // 5秒窗口
bool pirTriggeredInWindow = false;
bool soundTriggeredInWindow = false;
bool inTriggerWindow = false;

int detectPirSensor(int sensorPin){
    int sensorValue = digitalRead(sensorPin); // 读取人体传感器值
    if (sensorValue == HIGH) {
        return 1; // 传感器被触发
    } else {
        return 0; // 传感器未被触发
    }
}

int detectSoundSensor(int sensorPin, int threshold) {
    int value = analogRead(sensorPin); // 读取声音传感器模拟值
    if (value > threshold) {
        return 1; // 超过阈值
    } else {
        return 0; // 未超过阈值
    }
}

void setup() {
    pinMode(pirSensorPin, INPUT); // 人体传感器
    pinMode(lightSensorPin, INPUT); // 光敏传感器
    pinMode(ledPin, OUTPUT); // LED
    Serial.begin(9600); // 初始化串口通信
}

void printSensorStatus() {
    // 读取并更新传感器数值
    lightSensorState = digitalRead(lightSensorPin);
    pirSensorState = detectPirSensor(pirSensorPin);
    soundSensorValue = analogRead(soundSensorPin);
    soundSensorState = detectSoundSensor(soundSensorPin, soundThreshold);
    Serial.print("PIR Sensor: ");
    Serial.println(pirSensorState);
    Serial.print("Sound Sensor Value: ");
    Serial.println(soundSensorValue);
    Serial.print("Sound Sensor State: ");
    Serial.println(soundSensorState);
    Serial.print("Light Sensor: ");
    Serial.println(lightSensorState);
}

void loop() {
    printSensorStatus();
    if (lightSensorState == 1) { // 光敏传感器满足
        // 检查是否进入触发窗口
        if (!inTriggerWindow && (pirSensorState == 1 || soundSensorState == 1)) {
            inTriggerWindow = true;
            triggerWindowStart = millis();
            pirTriggeredInWindow = (pirSensorState == 1);
            soundTriggeredInWindow = (soundSensorState == 1);
        }
        // 如果已在窗口内，持续记录触发状态并循环输出状态
        if (inTriggerWindow) {
            while (millis() - triggerWindowStart <= triggerWindowDuration) {
                printSensorStatus();
                if (pirSensorState == 1) pirTriggeredInWindow = true;
                if (soundSensorState == 1) soundTriggeredInWindow = true;
                if (pirTriggeredInWindow && soundTriggeredInWindow) {
                    digitalWrite(ledPin, HIGH);
                    delay(3000); // 点亮3秒
                    digitalWrite(ledPin, LOW);
                    // 重置窗口
                    inTriggerWindow = false;
                    pirTriggeredInWindow = false;
                    soundTriggeredInWindow = false;
                    delay(200); // 防止误触发
                    break;
                }
                delay(100);
            }
            // 超时后重置窗口
            inTriggerWindow = false;
            pirTriggeredInWindow = false;
            soundTriggeredInWindow = false;
        } 
    } else {
        // 光敏不满足，重置窗口
        inTriggerWindow = false;
        pirTriggeredInWindow = false;
        soundTriggeredInWindow = false;
        digitalWrite(ledPin, LOW);
    }
    delay(100);
}



