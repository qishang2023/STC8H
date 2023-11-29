#include "bsp_Nixie.h"
#include "bsp_UART.h"
#include "bsp_I2C.h"
#include "Delay.h"
#include "bsp_Timer.h"
#include "bsp_RTC.h"
#include "bsp_oled_SPI.h"

extern u8 dat[7];

void main(){
 // 设备地址 read A3h and write A2h
    u8 dev_addr = 0x51 << 1; 	// (设备地址 << 1) | 0 = 写地址. 
    // 存储地址
    u8 mem_addr = 0x02;
    // 用于接收从机传来的数据
    u8 tem[7]={0x50,0x35,0x21,0x31,0x00,0x12,0x23};
    // RTC_clock clock;
	// 保存时间信息
    // u8 second, minute, hour, day, week, month;
    // u16 year;

    // 开启扩展寄存器使能
    EAXSFR();

    bsp_I2C_init();
    OLED_Init();
    UART_init();
    nixie_init();
    Timer_init();

    OLED_Clear();

    EA = 1;

//		4. 通过I2C给RTC时钟芯片写数据
    I2C_WriteNbyte(dev_addr, mem_addr, tem, 7);


    printf("--------------------------------read\n");
    while(1) {



/*         nixie_display((int)(dat[2] >> 4),1);
        nixie_display((int)(dat[2] & 0x0F),2);
        nixie_display(21,3);
        nixie_display((int)(dat[1] >> 4),4);
        nixie_display((int)(dat[1] & 0x0F),5); 
        nixie_display(21,6); 
        nixie_display((int)(dat[0] >> 4),7); 
        nixie_display((int)(dat[0] & 0x0F),8);  */

        OLED_ShowNum(90,0, clock.day, 2,16);
        OLED_ShowChar(72,0, '-');
        // OLED_ShowNum(54,0, clock.week, 2,16);
        OLED_ShowNum(54,0, clock.month, 2,16);
        OLED_ShowChar(36,0, '-');
        OLED_ShowNum(0,0, clock.year, 4,16);

        OLED_ShowNum(72,2, clock.second, 2,16);
        OLED_ShowChar(54,2, ':');
        OLED_ShowNum(36,2, clock.minute, 2,16);
        OLED_ShowChar(18,2, ':');
        OLED_ShowNum(0,2, clock.hour, 2,16);

    }
}