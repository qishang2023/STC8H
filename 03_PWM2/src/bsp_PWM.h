#ifndef __BSP_PWM_H
#define __BSP_PWM_H

#include "GPIO.h"
#include "STC8H_PWM.h"
#include "NVIC.h"
#include "Switch.h"

#define PERIOD (MAIN_Fosc / 1000UL)

void PWM_init();
void PWM_set(u8 duty_percent);

#endif // !__BSP_PWM_H
