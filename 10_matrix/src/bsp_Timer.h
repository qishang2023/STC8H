#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#include "Timer.h"
#include "NVIC.h"

extern u32 sys_time;
extern u8 key_num;

void Timer_init();

#endif // !__BSP_TIMER_H