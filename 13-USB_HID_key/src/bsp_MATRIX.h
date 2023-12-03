#ifndef __BSP_MATRIX_H
#define __BSP_MATRIX_H

#include "GPIO.h"

#define KCOL1 P03
#define KCOL2 P06
#define KCOL3 P07
#define KCOL4 P17
#define KROW1 P34
#define KROW2 P35
#define KROW3 P40
#define KROW4 P41

extern u8 matrix_num;
extern u16 matrix_state;

void MATRIX_init();
void matrix_loop();
void matrix_GetState();

#endif // !__BSP_MATRIX_H