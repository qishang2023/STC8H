//////////////////////////////////////////////////////////////////////////////////
// 本程序只供学习使用，未经作者许可，不得用于其它任何用途
// 中景园电子
// 店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//   文 件 名   : main.c
//   版 本 号   : v2.0
//   作    者   : HuangKai
//   生成日期   : 2014-0101
//   最近修改   :
//   功能描述   : OLED 4接口演示例程(51系列)
//               说明:
//               ----------------------------------------------------------------
//               GND    电源地
//               VCC  接5V或3.3v电源
//               D0   P1^0（SCL）
//               D1   P1^1（SDA）
//               RES  接P12
//               DC   接P13
//               CS   接P14
//               ----------------------------------------------------------------
//  修改历史   :
//  日    期   :
//  作    者   : HuangKai
//  修改内容   : 创建文件
// 版权所有，盗版必究。
// Copyright(C) 中景园电子2014/3/16
// All rights reserved
//******************************************************************************/
#include "config.h"
#include "bsp_OLED_SPI.h"
#include "bmp.h"
#include "GPIO.h"
#include "bsp_RTC.h"
#include "bsp_DHT11.H"

int main(void)
{
    float t;
    u8 h;
    u8 buf[20];
    EAXSFR();
    OLED_Init(); // 初始化OLED
    Timer_init();
    bsp_I2C_init();
    DHT11_init();
    OLED_Clear();
    EA = 1;
    OLED_Clear();
    // 设置clock时间
    clock.year   = 2023;
    clock.month  = 12;
    clock.day    = 2;
    clock.week   = 6;
    clock.hour   = 11;
    clock.minute = 48;
    clock.second = 0;
    RTC_SetTime(&clock);
    while (1) {
        OLED_Display_GB2312_string(0, 0, "赵修伟是天才！");
        if (start_DHT11 == 1) {
            start_DHT11 = 0;
            // OLED_Clear();
            if (DHT11_get_temperature(&h, &t) == 0) {
                sprintf((char *)buf, "温度：%.1f", t);
                OLED_Display_GB2312_string(0, 2, buf);
                sprintf((char *)buf, "湿度：%d%%", (int)h);
                OLED_Display_GB2312_string(0, 4, buf);
            }
            if (clock.minute <= 9 && clock.second <= 9) {
                sprintf((char *)buf, "时间：%d:0%d:0%d\0", (int)clock.hour, (int)clock.minute, (int)clock.second);
            } else if (clock.minute <= 9) {
                sprintf((char *)buf, "时间：%d:0%d:%d\0", (int)clock.hour, (int)clock.minute, (int)clock.second);
            } else if (clock.second <= 9) {
                sprintf((char *)buf, "时间：%d:%d:0%d\0", (int)clock.hour, (int)clock.minute, (int)clock.second);
            } else {
                sprintf((char *)buf, "时间：%d:%d:%d\0", (int)clock.hour, (int)clock.minute, (int)clock.second);
            }
            OLED_Display_GB2312_string(0, 6, buf);
        }
    }
}