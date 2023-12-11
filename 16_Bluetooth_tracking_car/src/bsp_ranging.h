#ifndef __BSP_RANGING_H
#define __BSP_RANGING_H

#include "GPIO.h"

//trig Ϊ�����˿�
//echo Ϊ���ն˿�
#define ECHO P40
#define TRIG P13

float ranging_get_distance(void);
void ranging_init(void);

#endif // !__BSP_RANGING_H
