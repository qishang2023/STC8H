#include "BSP_MATRIX.h"
u8 matrix_num;
u16 matrix_state = 0;

void MATRIX_init()
{
    P0_MODE_IO_PU(GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
    P1_MODE_IO_PU(GPIO_Pin_7);
    P3_MODE_IO_PU(GPIO_Pin_4 | GPIO_Pin_5);
    P4_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);
}

void matrix_GetState()
{
    matrix_state = 0;
    KROW1 = 0;
    NOP1();
    if (KCOL1 == 0) { matrix_state |= 1; }
    if (KCOL2 == 0) { matrix_state |= (1 << 1); }
    if (KCOL3 == 0) { matrix_state |= (1 << 2); }
    if (KCOL4 == 0) { matrix_state |= (1 << 3); }
    KROW1 = 1;
    NOP1();

    KROW2 = 0;
    NOP1();
    if (KCOL1 == 0) { matrix_state |= (1 << 4); }
    if (KCOL2 == 0) { matrix_state |= (1 << 5); }
    if (KCOL3 == 0) { matrix_state |= (1 << 6); }
    if (KCOL4 == 0) { matrix_state |= (1 << 7); }
    KROW2 = 1;
    NOP1();

    KROW3 = 0;
    NOP1();
    if (KCOL1 == 0) { matrix_state |= (1 << 8); }
    if (KCOL2 == 0) { matrix_state |= (1 << 9); }
    if (KCOL3 == 0) { matrix_state |= (1 << 10); }
    if (KCOL4 == 0) { matrix_state |= (1 << 11); }
    KROW3 = 1;
    NOP1();

    KROW4 = 0;
    NOP1();
    if (KCOL1 == 0) { matrix_state |= (1 << 12); }
    if (KCOL2 == 0) { matrix_state |= (1 << 13); }
    if (KCOL3 == 0) { matrix_state |= (1 << 14); }
    if (KCOL4 == 0) { matrix_state |= (1 << 15); }
    KROW4 = 1;
    NOP1();
}

void matrix_loop()
{
    static u16 before_state, now_state,temp1,temp2;
    u8  i;
    before_state  = matrix_state;
    matrix_GetState();
    now_state = matrix_state;
    for (i = 0; i < 16; i++) {
        temp1 = before_state;
        temp2 = now_state;
        if (((temp1 == (1 << i)) != 0) && ((temp2 &= (1 << i)) == 0)) matrix_num = i + 1;
    }    
}