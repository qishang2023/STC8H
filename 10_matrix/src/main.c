#include "bsp_Timer.h"
#include "bsp_UART.h"
#include "BSP_MATRIX.h"


void main(){
    UART_init();
    Timer_init();
    MATRIX_init();
    EA = 1;
    printf("test...");
    while (1)
    {
        if(matrix_num != 0){
            printf("matrix_num = %d\n",(int)matrix_num);
            matrix_num = 0;
        }
    }
    

}