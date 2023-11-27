#ifndef __BSP_DHT11_H
#define __BSP_DHT11_H

#include "GPIO.h"
#include "bsp_Timer.h"
#include "Delay.h"

#define DHT P46

void DHT11_init();
u8 DHT11_get_temperature(u8 *humidity, float *temperature);

#endif // !__BSP_DHT11_H