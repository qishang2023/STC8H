#include "config.h"
#include "bsp_OLED_SPI.h"
#include "bmp.h"
#include "GPIO.h"
#include "bsp_RTC.h"
#include "bsp_DHT11.H"
#include "UART.h"

void bluetooh_init()
{
    COMx_InitDefine COMx_InitStructure;                 
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx; 
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;     
    COMx_InitStructure.UART_BaudRate  = 115200ul;       
    COMx_InitStructure.UART_RxEnable  = ENABLE;        
    COMx_InitStructure.BaudRateDouble = DISABLE; 
    UART_Configuration(UART1, &COMx_InitStructure);
    NVIC_UART1_Init(ENABLE, Priority_1); 
    UART1_SW(UART1_SW_P30_P31);

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer4;
    COMx_InitStructure.UART_BaudRate  = 9600ul; 
    COMx_InitStructure.UART_RxEnable  = ENABLE; 
    COMx_InitStructure.BaudRateDouble = DISABLE;
    UART_Configuration(UART4, &COMx_InitStructure);

    NVIC_UART4_Init(ENABLE, Priority_2);
    UART4_SW(UART4_SW_P02_P03);
    P0_MODE_IO_PU(GPIO_Pin_2 | GPIO_Pin_3);
}

void do_control()
{
    if (RX4_Buffer[0] != 0x53 || RX4_Buffer[1] != 0x54) {
        return;
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
    OLED_Init(); 
    Timer_init();
    bsp_I2C_init();
    DHT11_init();
    bluetooh_init();
    OLED_Clear();
    EA = 1;
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
            if (--COM4.RX_TimeOut == 0) {
                if (COM4.RX_Cnt > 0) {
                    for (i = 0; i < COM4.RX_Cnt; i++) {
                        do_control();
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
/*             if (clock.minute <= 9 && clock.second <= 9) {
                sprintf((char *)buf, "时间：%d:0%d:0%d  \0", (int)clock.hour, (int)clock.minute, (int)clock.second);
            } else if (clock.minute <= 9) {
                sprintf((char *)buf, "时间：%d:0%d:%d  \0", (int)clock.hour, (int)clock.minute, (int)clock.second);
            } else if (clock.second <= 9) {
                sprintf((char *)buf, "时间：%d:%d:0%d  \0", (int)clock.hour, (int)clock.minute, (int)clock.second);
            } else {
                sprintf((char *)buf, "时间：%d:%d:%d  \0", (int)clock.hour, (int)clock.minute, (int)clock.second);
            } */
            sprintf((char *)buf, "时间：%02d:%02d:%02d", (int)clock.hour, (int)clock.minute, (int)clock.second);
            OLED_Display_GB2312_string(0, 6, buf);
        }
    }
}