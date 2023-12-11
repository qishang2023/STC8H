#include "bsp_track.h"

u8 track_state = 0;

void track_init(void)
{
    P0_MODE_IO_PU(GPIO_Pin_6);
    P3_MODE_IO_PU(GPIO_Pin_2 | GPIO_Pin_3);
    P4_MODE_IO_PU(GPIO_Pin_7);
    P5_MODE_IO_PU(GPIO_Pin_0);
}

void trcak_get_state(void)
{
    track_state = 0;
    if(TRACK_R == 0)
    {
        track_state |= 0x01;
    }
    if(TRACK_MR == 0)
    {
        track_state |= 0x02;
    }
    if(TRACK_M == 0)
    {
        track_state |= 0x04;
    }
    if(TRACK_ML == 0)
    {
        track_state |= 0x08;
    }
    if(TRACK_L == 0)
    {
        track_state |= 0x10;
    }
}