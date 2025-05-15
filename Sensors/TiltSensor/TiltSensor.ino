// 倾斜传感器
const uint8_t tiltSensorPin = 2; // 倾斜传感器引脚
const uint8_t ledPin = 13; // LED引脚

int tiltSensorState = 0; // 储存传感器状态

void setup() {
  pinMode(tiltSensorPin, INPUT); // 设置倾斜传感器引脚为输入
  pinMode(ledPin, OUTPUT); // 设置LED引脚为输出
  Serial.begin(9600); // 初始化串口通信
}

void loop() {
  tiltSensorState = digitalRead(tiltSensorPin); // 读取倾斜传感器状态

  if (tiltSensorState == HIGH) { // 如果传感器被触发
    digitalWrite(ledPin, HIGH); // 点亮LED
    } 
  else {
    digitalWrite(ledPin, LOW); // 熄灭LED
}

  delay(500);
}