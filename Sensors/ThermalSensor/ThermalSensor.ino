// 热传感器
const int thermalSensorPin = 2; // 热传感器引脚
const int ledPin = 13; // LED引脚

int thermalSensorState = 0; // 储存传感器值

void setup() {
  pinMode(thermalSensorPin, INPUT); // 设置热传感器引脚为输入
  pinMode(ledPin, OUTPUT); // 设置LED引脚为输出
  Serial.begin(9600); // 初始化串口通信
}

void loop() {
  thermalSensorState = digitalRead(thermalSensorPin); // 读取热传感器值

  Serial.println(thermalSensorState, BIN); // 打印传感器值到串口监视器

  if (thermalSensorState == 1) { 
    digitalWrite(ledPin, HIGH); // 点亮LED
} 
  else {
    digitalWrite(ledPin, LOW); // 熄灭LED
}

  delay(500);
}