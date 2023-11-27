#ifndef __BSP_RTC_H
#define __BSP_RTC_H


#include "bsp_I2C.h"


// 设备地址
#define		PCF8563_ADDR  0x51 << 1
// 存储地址：时间的存储地址开始位置
#define		PCF8563_REG_TD   0x02

#endif // !__BSP_RTC_H