#include "usb.h"

void sys_init();

void main()
{
	P_SW2 |= 0x80;  //扩展寄存器(XFR)访问使能

    usb_init();
    EA = 1;
    
    while (1);
}