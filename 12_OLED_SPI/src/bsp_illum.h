#ifndef __BSP_ILLUM_H
#define __BSP_ILLUM_H

#include "I2C.h"

#define ILLUMDRESS 0x46

extern u16 illum_num;

void bsp_illum_get_data(void);
void bsp_illum_init();

#endif // !__BSP_ILLUM_H
