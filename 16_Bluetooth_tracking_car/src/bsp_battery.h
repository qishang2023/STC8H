#ifndef __BSP_BATTERY_H
#define __BSP_BATTERY_H

#include "GPIO.h"
#include "ADC.h"

void battery_init();
float Battery_get_voltage();

#endif // !__BSP_BATTERY_H
