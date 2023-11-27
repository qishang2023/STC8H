#include "bsp_UART.h"
#include "bsp_KEY.H"
#include "bsp_Timer.h"
#include "Delay.h"

void main(){
    u8 last_key_state =0;
    UART_init();
    KEY_init();
    Timer_init();

    EA = 1;
    printf("test...");
    while (1)
    {
        if(key_num != 0){
            if (key_num == 1)
            {
               printf("key number = %d ,int = %d\n",(int)key_num,(int)sizeof(int));
            }            
            // printf("key number = %x\n",key_num);
            key_num = 0;
        }
    }
    
}
