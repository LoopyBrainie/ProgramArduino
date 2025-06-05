#include "Seg7.h"

/* 宏定义 */
#define RED_DAY_TIME   10000 // 红灯白天持续时间（毫秒）
#define RED_NIGHT_TIME 5000 // 红灯夜间持续时间（毫秒）
#define GREEN_DAY_TIME 10000 // 绿灯白天持续时间（毫秒）
#define GREEN_NIGHT_TIME 5000 // 绿灯夜间持续时间（毫秒）
#define YELLOW_TIME    3000 // 黄灯持续时间（毫秒）

#define GREEN_BLINK_TIME  500 // 绿灯开始闪烁时间（毫秒）
#define GREEN_BLINK_LAGLAG 3 // 绿灯闪烁间隔（毫秒）
#define ACCIDENT_BLINK_TIME 500 // 事故红灯闪烁时间（毫秒）

#define RED_BEEP_CIRCAL 1000 // 红灯蜂鸣周期（毫秒）
#define GREEN_BEEP_CIRCAL 500 // 绿灯蜂鸣周期（毫秒）
#define ACCIDENT_BEEP_CIRCAL 5000 // 事故蜂鸣周期（毫秒）
#define NORMAL_BEEP_TIME 100 // 正常蜂鸣时长（毫秒）
#define ACCIDENT_BEEP_TIME 1000 // 事故蜂鸣时长（毫秒）

