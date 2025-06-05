#include <DHT.h>

const int DHTpin = 2; // DHT传感器引脚
const int DHTtype = DHT11;  // DHT传感器类型

DHT dht(DHTpin, DHTtype); // 创建DHT传感器对象

float tempC;// 摄氏温度变量
float tempF; // 华氏温度变量
float humi;

void setup() {
    Serial.begin(9600);
    dht.begin();
}
void loop() {
    delay(2000); // 等待2秒以获取稳定的读数
    float h = dht.readHumidity(); // 读取湿度
    float t = dht.readTemperature(); // 读取摄氏温度

    // 检查是否有读取错误
    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%, Temperature: ");
    Serial.print(t);
    Serial.println("°C");
}