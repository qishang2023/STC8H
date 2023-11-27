#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "GPIO.h"

#define LED0 P53
#define LED1 P27
#define LED2 P26
#define LED3 P15
#define LED4 P14
#define LED5 P23
#define LED6 P22
#define LED7 P21
#define LED8 P20


void LED_init();
void ToggleLed(u8 Led);
void CloseLEd(u8 Led);
void OpenLed(u8 Led);
#endif // !__BSP_LED_H