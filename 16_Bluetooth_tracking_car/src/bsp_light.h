#ifndef __BSP_LIGHT_H
#define __BSP_LIGHT_H

#include "GPIO.h"

#define LED_R P05
#define LED_L P34

void light_init(void);
void light_toggle(u8 num);

#endif // !__BSP_LIGHT_H