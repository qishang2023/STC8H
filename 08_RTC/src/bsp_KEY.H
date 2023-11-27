#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "GPIO.h"
#include "Switch.h"

#define KEY1 P51
#define KEY2 P52
#define KEY3 P53
#define KEY4 P54

extern u8 key_num;

void KEY_init();
void key_loop();

#endif // !__BSP_KEY_H