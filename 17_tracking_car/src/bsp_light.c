#include "bsp_light.h"

void light_init(void)
{
    P0_MODE_OUT_PP(GPIO_Pin_5);
    P3_MODE_OUT_PP(GPIO_Pin_4);
}

void light_toggle(u8 num){
    if (num == 0)
    {
       LED_L = ~LED_L;
    }else if (num == 1)
    {
        LED_R = ~LED_R;
    }else
    {
         LED_L = ~LED_L;
         LED_R = ~LED_R;
    }     
}