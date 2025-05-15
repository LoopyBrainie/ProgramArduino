// 光敏传感器
const uint8_t lightSensorPin = 2;  // 定义光敏传感器引脚
const uint8_t ledPin = 13;         // 定义LED指示灯引脚

void setup() {
    Serial.begin(9600);              // 初始化串口通信
    pinMode(lightSensorPin, INPUT);  // 设置光敏传感器为输入模式
    pinMode(ledPin, OUTPUT);         // 设置LED为输出模式
}

void loop() {
    int lightValue = digitalRead(lightSensorPin);  // 读取光敏传感器值
    
    Serial.print("Light sensor value: ");
    Serial.println(lightValue);
    
    // 根据光线强度控制LED
    if (lightValue == HIGH) {
        digitalWrite(ledPin, HIGH);     // 光线弱时LED关闭
    } else {
        digitalWrite(ledPin, LOW);    // 光线强时LED点亮
    }
    
    delay(500);                      // 短暂延时
}
