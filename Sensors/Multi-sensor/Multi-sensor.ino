const uint8_t sensorCount = 2; // 传感器数量
const uint8_t lightSensorPin = 2;
const uint8_t ledPin = 13; 
uint8_t sensorPins[sensorCount]; 

int lightSensorState = 0; // 初始化光敏传感器状态
int sensorState[sensorCount] = {0}; // 初始化其余传感器状态

int detectSensor(int sensorPin){
    int sensorValue = digitalRead(sensorPin); // 读取传感器值
    if (sensorValue == HIGH) {
        return 1; // 传感器被触发
    } else {
        return 0; // 传感器未被触发
    }
}

void setup() {
    
    for(uint8_t i = 0; i < sensorCount; i++) {
        sensorPins[i] = i + 3; // 自动化赋值传感器引脚
    } //自动化赋值传感器
    for(uint8_t i = 0; i < sensorCount; i++) {
        pinMode(sensorPins[i], INPUT); // 设置传感器引脚为输入模式
    }
    pinMode(lightSensorPin, INPUT); // 设置光敏传感器引脚为输入模式
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
    lightSensorState = detectSensor(lightSensorPin); // 检测光敏传感器状态
    Serial.print("light Sensor: ");
    Serial.println(lightSensorState);

    // 控制LED灯
    bool allSensorTriggered = false;
    for(uint8_t i = 0; i < sensorCount; i++) {
        if(sensorState[i] == 1) {
            allSensorTriggered = true;
        }
    }

        if (lightSensorState == 1 && allSensorTriggered) {
            digitalWrite(ledPin, HIGH); // 打开LED灯
        } else {
            digitalWrite(ledPin, LOW); // 关闭LED灯
        }

    delay(500);

}



