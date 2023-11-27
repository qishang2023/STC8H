#include "bsp_LED.h"
#include "Delay.h"


void main(){
    LED_init();
    while (1)
    {
        ToggleLed(0);
        delay_ms(250);
        delay_ms(250);
        // P53 = 1;
        // NOP1();
        // P53 = 0;
        // ToggleLed(0);     
    }
    

}