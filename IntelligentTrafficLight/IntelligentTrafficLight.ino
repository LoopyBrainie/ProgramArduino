#include "Seg7.h"


/* 宏定义 */
#define RED_DAY_TIME     10000 // 红灯白天持续时间（毫秒）
#define RED_NIGHT_TIME   5000  // 红灯夜间持续时间（毫秒）
#define GREEN_DAY_TIME   10000 // 绿灯白天持续时间（毫秒）
#define GREEN_NIGHT_TIME 5000  // 绿灯夜间持续时间（毫秒）
#define YELLOW_TIME      3000  // 黄灯持续时间（毫秒）

#define GREEN_BLINK_TIME    500 // 绿灯开始闪烁时间（毫秒）
#define GREEN_BLINK_INT     3   // 绿灯闪烁间隔（毫秒）
#define ACCIDENT_BLINK_TIME 500 // 事故红灯闪烁时间（毫秒）

#define RED_BEEP_CIRCAL      1000 // 红灯蜂鸣周期（毫秒）
#define GREEN_BEEP_CIRCAL    500  // 绿灯蜂鸣周期（毫秒）
#define ACCIDENT_BEEP_CIRCAL 5000 // 事故蜂鸣周期（毫秒）
#define NORMAL_BEEP_TIME     100  // 正常蜂鸣时长（毫秒）
#define ACCIDENT_BEEP_TIME   1000 // 事故蜂鸣时长（毫秒）


/* 引脚定义 */
const uint8_t RED_PIN = 2;                           // 红灯引脚
const uint8_t GREEN_PIN = 3;                         // 绿灯引脚
const uint8_t YELLOW_PIN = 4;                        // 黄灯引脚
const uint8_t SEG_PINS[7] = {5, 6, 7, 8, 9, 10, 11}; // 数码管阴极引脚
const uint8_t BEEP_PIN = 12;                         // 蜂鸣器引脚（低电平）
const uint8_t BTN_PIN = 13;                          // 行人过街按钮引脚（低电平）
const uint8_t PHOTORES_PIN = A0;                     // 光敏电阻引脚（模拟输入）
const uint8_t MIC_PIN = A1;                          // 麦克风引脚（模拟输入）


/* 类型定义 */
//交通灯状态
typedef enum State_t {
    RED,     // 红灯
    GREEN,   // 绿灯
    YELLOW,  // 黄灯
    ACCIDENT // 事故状态
} State_t;


/* 全局变量 */
int RedTime = RED_DAY_TIME;     // 红灯持续时间（毫秒）
int GreenTime = GREEN_DAY_TIME; // 绿灯持续时间（毫秒）
State_t LightState = RED;       // 交通灯状态
int LightTime = RedTime;        // 交通灯剩余时间（毫秒）
int BlinkTime = 0;              //闪烁计时变量（毫秒）
int BeepTime = 0;               //蜂鸣计时变量（毫秒）
uint32_t Tick = 0;              //当前tick时刻（毫秒）


/* 任务定义 */
//交通灯任务
void TaskLight() {
    static uint32_t lastTick = 0; // 上次状态切换的tick时刻

    //每毫秒执行一次
    if (lastTick != Tick) {
        lastTick = Tick;
        lastTime--;

        //根据计时切换交通灯
        if (LightTime <= 0) {
            switch (LightState) {
                case RED:
                    LightState = GREEN;    // 切换到绿灯
                    LightTime = GreenTime; // 设置绿灯持续时间
                    break;
                case GREEN:
                    LightState = YELLOW;     // 切换到黄灯
                    LightTime = YELLOW_TIME; // 设置黄灯持续时间
                    break;
                case YELLOW:
                    LightState = RED;    // 切换到红灯
                    LightTime = RedTime; // 设置红灯持续时间
                    break;
                case ACCIDENT:
                    LightTime = 0;
                    break;
            } 
        }

        //根据状态切换交通灯
        switch (LightState) {
            case RED:
                digitalWrite(RED_PIN, HIGH);   // 红灯亮
                digitalWrite(GREEN_PIN, LOW);  // 绿灯灭
                digitalWrite(YELLOW_PIN, LOW); // 黄灯灭
                break;
            case GREEN:
                if (LightTime <= GREEN_BLINK_TIME) { // 绿灯最后时间闪烁
                    BlinkTime++; // 增加闪烁计时
                    if (BlinkTime < GREEN_BLINK_INT) {
                        digitalWrite(GREEN_PIN, LOW);  /// 每个闪烁周期前半段绿灯灭
                    } else if (BlinkTime < GREEN_BLINK_INT * 2) {
                        digitalWrite(GREEN_PIN, HIGH); /// 每个闪烁周期后半段绿灯亮
                    } else {
                        BlinkTime = 0;                 /// 重置闪烁计时
                    }
                } else {                             //其他时间正常常亮
                    BlinkTime = 0;                 /// 重置闪烁计时
                    digitalWrite(RED_PIN, LOW);    /// 红灯灭
                    digitalWrite(GREEN_PIN, HIGH); /// 绿灯亮
                    digitalWrite(YELLOW_PIN, LOW); /// 黄灯灭
                }
                break;
            case YELLOW:
                digitalWrite(RED_PIN, LOW);     // 红灯灭
                digitalWrite(GREEN_PIN, LOW);   // 绿灯灭
                digitalWrite(YELLOW_PIN, HIGH); // 黄灯亮
                break;
            case ACCIDENT:
                digitalWrite(RED_PIN, HIGH);  // 红灯亮
                digitalWrite(GREEN_PIN, LOW); // 绿灯灭
                BlinkTime++;                  // 增加闪烁计时
                if (BlinkTime < ACCIDENT_BLINK_TIME) {
                    digitalWrite(RED_PIN, LOW);  // 每个事故灯闪烁周期前半段红灯灭
                } else if (BlinkTime < ACCIDENT_BLINK_TIME * 2) {
                    digitalWrite(RED_PIN, HIGH); // 红灯灭
                } else {
                    BlinkTime = 0;               // 重置闪烁计时
                }
                break;
        }
    }
}

//数码管任务
void TaskSeg() {
    static uint8_t lastTime = 0; // 上次显示的时间
    uint8_t time = (uint8_t)(lastTime / 1000);
    if (time >9) {
        time = 9; // 限制显示范围为0-9
    }

    //每秒（秒数变化）执行一次
    if (lastTime != Tick / 1000) {
        lastTime = time;
        seg7_display(time); // 显示当前时间
    }
}

//蜂鸣器任务

//按键任务

//白天与黑夜模式切换任务

//事故检测报警任务


/* 初始化 */
void setup() {
    // 初始化引脚
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);
    pinMode(BEEP_PIN, OUTPUT);
    pinMode(BTN_PIN, INPUT_PULLUP); // 按键引脚使用上拉电阻
    pinMode(PHOTORES_PIN, INPUT);   // 光敏电阻引脚
    pinMode(MIC_PIN, INPUT);        // 麦克风引脚

    // 初始化数码管
    seg7_init(SEG_PINS);

    // 初始化交通灯状态
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);

    // 初始化蜂鸣器
    digitalWrite(BEEP_PIN, LOW);
}


/* 主循环 */
void loop() {
    Tick = millis(); // 获取当前tick时刻（毫秒）

    TaskLight(); // 执行交通灯任务
    TaskSeg();   // 执行数码管任务

    TaskBeep();
    TaskBTN();
    TaskDayNight();
    TaskAccidentCheck();
}