#include "BSP_MATRIX.h"

u8 matrix_num = 0;

void MATRIX_init(){
    P0_MODE_IO_PU(GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
    P1_MODE_IO_PU( GPIO_Pin_7);
    P3_MODE_IO_PU(GPIO_Pin_4 | GPIO_Pin_5);
    P4_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);
}

u8 matrix_GetState()
{
	unsigned char keynum = 0;
    KROW1 = 0;
    NOP1();
	if(KCOL1==0){keynum=1;}	
	if(KCOL2==0){keynum=2;}
	if(KCOL3==0){keynum=3;}
	if(KCOL4==0){keynum=4;}
    KROW1 = 1;
    NOP1();

    if(keynum != 0)return keynum;

    KROW2 = 0;
    NOP1();
	if(KCOL1==0){keynum=5;}	
	if(KCOL2==0){keynum=6;}
	if(KCOL3==0){keynum=7;}
	if(KCOL4==0){keynum=8;}
    KROW2 = 1;
    NOP1();
    if(keynum != 0)return keynum;

    KROW3 = 0;
    NOP1();
	if(KCOL1==0){keynum=9;}	
	if(KCOL2==0){keynum=10;}
	if(KCOL3==0){keynum=11;}
	if(KCOL4==0){keynum=12;}
    KROW3 = 1;
    NOP1();
    if(keynum != 0)return keynum;

    KROW4 = 0;
    NOP1();
	if(KCOL1==0){keynum=13;}
	if(KCOL2==0){keynum=14;}
	if(KCOL3==0){keynum=15;}
	if(KCOL4==0){keynum=16;}
    KROW4 = 1;
    NOP1();
	return keynum;
}

void matrix_loop(){
    static u8 before_state,now_state;
	before_state = now_state;
    now_state = matrix_GetState();
    
    if(before_state == 1 && now_state == 0)	    matrix_num = 1;
    if(before_state == 2 && now_state == 0)	    matrix_num = 2;
    if(before_state == 3 && now_state == 0)	    matrix_num = 3;
    if(before_state == 4 && now_state == 0)	    matrix_num = 4;
    if(before_state == 5 && now_state == 0)	    matrix_num = 5;
    if(before_state == 6 && now_state == 0)	    matrix_num = 6;
    if(before_state == 7 && now_state == 0)	    matrix_num = 7;
    if(before_state == 8 && now_state == 0)	    matrix_num = 8;
    if(before_state == 9 && now_state == 0)	    matrix_num = 9;
    if(before_state == 10 && now_state == 0)	matrix_num = 10;
    if(before_state == 11 && now_state == 0)	matrix_num = 11;
    if(before_state == 12 && now_state == 0)	matrix_num = 12;
    if(before_state == 13 && now_state == 0)	matrix_num = 13;
    if(before_state == 14 && now_state == 0)	matrix_num = 14;
    if(before_state == 15 && now_state == 0)	matrix_num = 15;
    if(before_state == 16 && now_state == 0)	matrix_num = 16;
}