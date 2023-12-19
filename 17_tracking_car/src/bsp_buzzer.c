#include "bsp_buzzer.h"

void Delay100us()		//@24.000MHz
{
	unsigned char data i, j;

	i = 4;
	j = 27;
	do
	{
		while (--j);
	} while (--i);
}

void buzzer_init()
{
    P3_MODE_OUT_PP(GPIO_Pin_6);
    BUZZER = 0;
}

void buzzer_beep(){
    u16 i = 1000;
    while(--i > 0){
        BUZZER = 1;
        Delay100us();
        BUZZER = 0;
        Delay100us();
    }
    BUZZER = 0;
}