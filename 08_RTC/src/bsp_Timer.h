#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#include "Timer.h"
#include "NVIC.h"
#include "bsp_KEY.H"
#include "bsp_RTC.h"
#include "I2C.h"

extern u32 sys_time;
extern RTC_clock clock;

void Timer_init();

#endif // !__BSP_TIMER_H