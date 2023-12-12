#ifndef __BSP_BUZZER_H
#define __BSP_BUZZER_H

#include "GPIO.h"

#define BUZZER P36

void buzzer_init();
void buzzer_beep();

#endif // !__BSP_BUZZER_H
