#include "usb.h"

void sys_init();

void main()
{
	P_SW2 |= 0x80;  //��չ�Ĵ���(XFR)����ʹ��

    usb_init();
    EA = 1;
    
    while (1);
}