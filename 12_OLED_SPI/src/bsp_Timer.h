#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#include "Timer.h"
#include "NVIC.h"
// #include "bsp_KEY.H"
#include "bsp_RTC.h"
#include "I2C.h"

extern u32 sys_time;
extern RTC_clock clock;
extern u8 start_DHT11;

void Timer_init();

#endif // !__BSP_TIMER_H