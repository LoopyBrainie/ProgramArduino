// 人体感应传感器(PIR Sensor)示例代码
const int pirSensorPin = 2;    // 人体感应传感器引脚
const int ledPin = 13;         // LED引脚

int pirSensorState = 0;              // 储存传感器状态

void setup() {
  pinMode(pirSensorPin, INPUT); // 设置人体感应传感器引脚为输入
  pinMode(ledPin, OUTPUT);      // 设置LED引脚为输出
  Serial.begin(9600);          // 初始化串口通信
}

void loop() {
  pirSensorState = digitalRead(pirSensorPin); // 读取传感器状态
  
  if (pirSensorState == HIGH) {             // 如果检测到人体移动
    digitalWrite(ledPin, HIGH);       // 点亮LED
    Serial.println("检测到移动！");    // 通过串口输出信息
  } else {
    digitalWrite(ledPin, LOW);        // 熄灭LED
    Serial.println("未检测到移动");    // 通过串口输出信息
  }
  
  delay(500);                         // 延时500毫秒
}