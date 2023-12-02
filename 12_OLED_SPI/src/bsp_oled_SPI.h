#ifndef __BSP_OLED_SPI_H
#define __BSP_OLED_SPI_H

#include "config.h"
#include "Delay.h"
#include "GPIO.h"

sbit OLED_SCL=P5^0;    
sbit OLED_SDA=P1^3;   
sbit OLED_DC=P1^6; 
sbit OLED_CS=P4^7;
sbit OLED_READ_FS0=P1^1;
sbit OLED_ROM_CS=P1^0;

#define u8  unsigned char
#define u32 unsigned long
#define OLED_CMD  0   //д����
#define OLED_DATA 1   //д����

#define OLED_SCL_Set()       OLED_SCL=1;
#define OLED_SCL_Clr()       OLED_SCL=0;

#define OLED_SDA_Set()       OLED_SDA=1;
#define OLED_SDA_Clr()       OLED_SDA=0;

#define OLED_DC_Set()        OLED_DC=1;
#define OLED_DC_Clr()        OLED_DC=0;

#define OLED_CS_Set()        OLED_CS=1;
#define OLED_CS_Clr()        OLED_CS=0;

#define OLED_ROM_CS_Set()    OLED_ROM_CS=1;
#define OLED_ROM_CS_Clr()    OLED_ROM_CS=0;

// void delay_ms(unsigned int ms);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Clear(void);
void OLED_address(u8 x,u8 y);
void OLED_Display_128x64(u8 *dp);
void OLED_Display_16x16(u8 x,u8 y,u8 *dp);
void OLED_Display_8x16(u8 x,u8 y,u8 *dp);
void OLED_Display_5x7(u8 x,u8 y,u8 *dp);
void Send_Command_to_ROM(u8 dat);
u8 Get_data_from_ROM(void);
void OLED_get_data_from_ROM(u8 addrHigh,u8 addrMid,u8 addrLow,u8 *pbuff,u8 DataLen);
void OLED_Display_GB2312_string(u8 x,u8 y,u8 *text);
void OLED_Display_string_5x7(u8 x,u8 y,u8 *text);
void OLED_ShowNum(u8 x,u8 y,float num,u8 len);
void OLED_Init(void);
#endif