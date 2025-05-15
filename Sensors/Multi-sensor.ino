const uint8_t sensorCount = 3; // 传感器数量
const uint8_t ledPin = 13; // Pin for the LED
uint8_t sensorPins[sensorCount]; // Dynamic array for sensor pins

int sensorState[sensorCount] = 0; // 初始化传感器状态

int detectSensor(sensorPin){
    int sensorValue = digitalRead(sensorPin); // 读取传感器值
    if (sensorValue == HIGH) {
        return 1; // 传感器被触发
    } else {
        return 0; // 传感器未被触发
    }
}

void setup() {
    for(uint8_t i = 0; i < sensorCount; i++) {
        sensorPins[i] = i + 2;
    } //自动化赋值传感器

    for(uint8_t i = 0; i < sensorCount; i++) {
        pinMode(sensorPins[i], INPUT); // 设置传感器引脚为输入模式
    }
    pinMode(ledPin, OUTPUT); // 设置LED引脚为输出模式
    Serial.begin(9600); // 初始化串口通信
}

void loop() {
    for(uint8_t i = 0; i < sensorCount; i++) {
        sensorState[i] = detectSensor(sensorPins[i]); // 检测传感器状态
        Serial.print("Sensor ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(sensorState[i]);
    }

    // 控制LED灯
    if (sensorState[0] == 1 || sensorState[1] == 1 || sensorState[2] == 1) {
        digitalWrite(ledPin, HIGH); // 打开LED灯
    } else {
        digitalWrite(ledPin, LOW); // 关闭LED灯
    }
    delay(500);
}



