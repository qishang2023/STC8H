#include "bsp_PWM.h"
#include "bsp_UART.h"
#include "Delay.h"

void main(){
    u8 duty_percent = 0,dat = 0;
    UART_init();
    PWM_init();
    EA = 1;
    PWM_set(duty_percent);
    while (1)
    {
        // delay_ms(20);
        // TX1_write2buff(0x01);
        dat = UART_getchar();
        if(dat != 0){        
            switch (dat){
                case 1:duty_percent = 0; break;
                case 2:duty_percent = 25; break;
                case 3:duty_percent = 50; break;
                case 4:duty_percent = 75; break;
                case 5:duty_percent = 100; break;         
                default:break;
            }
            PWM_set(duty_percent);
         }
    }
    
}