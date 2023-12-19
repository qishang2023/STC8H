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
#include "UART.h"

void bluetooh_init()
{
    COMx_InitDefine COMx_InitStructure;                 // 结构定义
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx; // 模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;     // 选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;       // 波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;         // 接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;        // 波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);     // 初始化串口1 UART1,UART2,UART3,UART4
    NVIC_UART1_Init(ENABLE, Priority_1);                // 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    UART1_SW(UART1_SW_P30_P31);

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx; // 模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer4;     // 选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 9600ul;         // 波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;         // 接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;        // 波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART4, &COMx_InitStructure);     // 初始化串口1 UART1,UART2,UART3,UART4

    NVIC_UART4_Init(ENABLE, Priority_2); // 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    UART4_SW(UART4_SW_P02_P03);          // 引脚选择, UART4_SW_P02_P03,UART4_SW_P52_P53
    P0_MODE_IO_PU(GPIO_Pin_2 | GPIO_Pin_3);
}

void do_control()
{
    if (RX4_Buffer[0] != 0x53 || RX4_Buffer[1] != 0x54) {
        return; // 不是,返回
    }
    clock.hour = (RX4_Buffer[7]-48)*10 +(RX4_Buffer[8]-48);
    clock.minute = (RX4_Buffer[9]-48)*10 +(RX4_Buffer[10]-48);
    RTC_SetTime(&clock);
}

int main(void)
{
    float t;
    u8 h, i;
    u8 buf[15];
    EAXSFR();
    OLED_Init(); // 初始化OLED
    Timer_init();
    bsp_I2C_init();
    DHT11_init();
    bluetooh_init();
    OLED_Clear();
    EA = 1;
    // 设置clock时间
    clock.year   = 2023;
    clock.month  = 12;
    clock.day    = 2;
    clock.week   = 6;
    clock.hour   = 11;
    clock.minute = 48;
    clock.second = 0;
    RTC_SetTime(&clock);
    printf("start\r\n");
    while (1) {
        OLED_Display_GB2312_string(0, 0, "赵修伟是天才！");
        if (COM1.RX_TimeOut > 0) {
            // 超时计数
            if (--COM1.RX_TimeOut == 0) {
                if (COM1.RX_Cnt > 0) {
                    for (i = 0; i < COM1.RX_Cnt; i++) {
                        TX4_write2buff(RX1_Buffer[i]);
                    }
                }
                COM1.RX_Cnt = 0;
            }
        }
        if (COM4.RX_TimeOut > 0) {
            // 超时计数
            if (--COM4.RX_TimeOut == 0) {
                if (COM4.RX_Cnt > 0) {
                    for (i = 0; i < COM4.RX_Cnt; i++) {
                        do_control();
                        // TX1_write2buff(RX4_Buffer[i]);
                    }
                }
                COM4.RX_Cnt = 0;
            }
        }
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