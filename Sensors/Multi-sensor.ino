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

}



