#ifndef __BSP_RTC_H
#define __BSP_RTC_H


#include "bsp_I2C.h"


// �豸��ַ
#define		PCF8563_ADDR  0x51 << 1
// �洢��ַ��ʱ��Ĵ洢��ַ��ʼλ��
#define		PCF8563_REG_TD   0x02

#define NUMBER 7

typedef struct{
    u8 second, minute, hour, day, month, week, C ;
    u16 year;
}RTC_clock;

void RTC_SetTime(RTC_clock *clock);
void RTC_ReadTime(RTC_clock *clock);

#endif // !__BSP_RTC_H