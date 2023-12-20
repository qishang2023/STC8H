#include "bsp_illum.h"

u16 illum_num = 0;

void bsp_illum_init(){
    illum_send_byte(0x01);
    illum_send_byte(0x10);
}

void bsp_illum_get_data(void)
{
    u8 dat[4];
    illum_ReadNbyte(ILLUMDRESS, dat, 4);
    printf("illum data: %d %d %d %d\n", (int)dat[0], (int)dat[1], (int)dat[2],(int)dat[3]);
    illum_num = (dat[0] << 8) + dat[1];
}