#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "GPIO.h"

#define KEY1 P37

extern u8 key_num;

void key_init();
void key_loop();

#endif // !__BSP_KEY_H