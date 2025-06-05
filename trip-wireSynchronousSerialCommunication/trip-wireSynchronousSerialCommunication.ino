#include <Ds1302.h>;

#define RX_DATA_LENGTH 20  // 接收数据长度

const uint8_t rtcCePin = 4; // RTC CE引脚
const uint8_t rtcIoPin = 3; // RTC IO引脚
const uint8_t rtcSclkPin = 2; // RTC SCLK引脚

const static char* weekDays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}; // 星期数组

Ds1302 rtc(rtcCePin, rtcSclkPin, rtcIoPin);

Ds1302::DateTime currentTime; // 当前时间对象
char rxData[RX_DATA_LENGTH] = {'\0'}; // 接收数据缓冲区
int rxPosition = 0; // 接收数据位置指针

uint8_t getNum(char* str, uint8_t count) {
    uint8_t val = 0; // 初始化结果
    while (count-- > 0) {
        val *= 10; // 每次乘以10
        val += (*str - '0'); // 将字符转换为数字并累加
        str++; // 移动到下一个字符
    }
    return val; // 返回结果
}

void printDateTime(const Ds1302::DateTime* dt) {
    Serial.print(F("20"));
    Serial.print(dt->year); // 年
    Serial.print('-');
    Serial.print(dt->month); // 月
    Serial.print('-');
    Serial.print(dt->day); // 日
    Serial.print(' ');
    Serial.print(weekDays[dt->dow-1]); // 星期
    Serial.print(' ');
    if (dt->hour < 10 ) Serial.print('0'); // 小时前补零
    Serial.print(dt->hour); // 小时
    Serial.print(':');
    if (dt->minute < 10 ) Serial.print('0'); // 分钟前补零 
    Serial.print(dt->minute); // 分钟
    Serial.print(':');
    if (dt->second < 10 ) Serial.print('0'); // 秒前补零
    Serial.print(dt->second); // 秒
}

void setup() {
    Serial.begin(9600); // 初始化串口通信
    rtc.init(); // 初始化RTC
    Serial.println(F("Input the date and time in the format: YY-MM-DD-W-hh:mm:ss:"));
    rtc.start(); // 启动RTC
}

void loop() {
    while (Serial.available()) {
        rxData[rxPosition] = Serial.read();// 初始化字符位置到串口结束符
        if (rxData[rxPosition] == '\n') { 
            if (rxPosition == RX_DATA_LENGTH - 1) { // 长度正确
                // 解析输入数据
                currentTime.year = getNum(rxData, 2); // 年
                currentTime.month = getNum(rxData + 3, 2); // 月
                currentTime.day = getNum(rxData + 6, 2); // 日
                currentTime.dow = getNum(rxData + 9, 1); // 星期
                currentTime.hour = getNum(rxData + 11, 2); // 小时
                currentTime.minute = getNum(rxData + 14, 2); // 分钟
                currentTime.second = getNum(rxData + 17, 2); // 秒
                Serial.print(F("Set time to: "));
                printDateTime(&currentTime);
                rtc.setDateTime(&currentTime); // 设置当前时间
            } else {
                Serial.println(F("Input error, please try again!"));
            }
            rxPosition = 0; // 重置接收位置
            memset(rxData, 0, RX_DATA_LENGTH); // 清空接收缓冲区
        } else if (rxPosition >= RX_DATA_LENGTH - 1) {
            Serial.println(F("Input too long, please try again!"));
            rxPosition = 0; // 重置接收位置
            memset(rxData, 0, RX_DATA_LENGTH); // 清空接收缓冲区
        } else {
            rxPosition++;
        }
    }
    rtc.getDateTime(&currentTime); // 获取当前时间
    printDateTime(&currentTime); // 打印当前时间
    delay(1000); // 每秒更新一次
}