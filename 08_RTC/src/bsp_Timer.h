#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#include "Timer.h"
#include "NVIC.h"

extern u32 sys_time;

void Timer_init();

#endif // !__BSP_TIMER_H