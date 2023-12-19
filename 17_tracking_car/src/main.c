#include "RTX51TNY.H"
#include "bsp_track.h"
#include "bsp_light.h"
#include "UART.h"
#include "NVIC.h"
#include "Switch.h"
#include "bsp_key.h"
#include "bsp_battery.h"
#include "bsp_ranging.h"
#include "bsp_motor.h"
#include "bsp_buzzer.h"
#include "Delay.h"

void UART_init()
{
    COMx_InitDefine COMx_InitStructure; // 结构定义

    P1_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx; // 模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;     // 选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;       // 波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;         // 接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;        // 波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);     // 初始化串口1 UART1,UART2,UART3,UART4
    NVIC_UART1_Init(ENABLE, Priority_1);                // 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    UART1_SW(UART1_SW_P30_P31);

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx; // 模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;     // 选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 9600ul;         // 波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;         // 接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;        // 波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART2, &COMx_InitStructure);     // 初始化串口1 UART1,UART2,UART3,UART4

    NVIC_UART2_Init(ENABLE, Priority_1); // 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    UART2_SW(UART2_SW_P10_P11);          // 引脚选择, UART2_SW_P10_P11,UART2_SW_P46_P47
}

void main()
{
    int pos, last_pos;
    double distance;
    EAXSFR();
    light_init();
    track_init();
    UART_init();
    key_init();
    ranging_init();
    motor_init();
    battery_init();
    buzzer_init();
    buzzer_beep();
    while (1) {
        pos = Track_get_position();
        // distance = ranging_get_distance();
        // if (distance < 30) {
        //     Motors_stop();
        //     buzzer_beep();
        //     continue;
        // }
        // 上次的pos和本次pos相同, 跳过本次循环, 避免频繁设置同样PWM
        if (last_pos == pos) {
            delay_ms(5);
            continue;
        }
        // pos 为负值 -> 左转, 为正值 -> 右转
        if (pos < -32) {
            Motors_stop();
            delay_ms(20);
            Motor_left(50);
        } else if (pos > 0) {
            // Motors_stop();
            // delay_ms(20);
            Motor_right_mini(20);
            delay_ms(100);
            Motors_forward(20);
        } else if (pos < 0) {
            // Motors_stop();
            // delay_ms(20);
            Motor_left_mini(20);
            delay_ms(100);
            Motors_forward(20);
        } else if (pos > 32) {
            Motors_stop();
            delay_ms(20);
            Motor_right(50);
        } else {
            Motors_forward(50);
        }
        last_pos = pos;
    }
}
