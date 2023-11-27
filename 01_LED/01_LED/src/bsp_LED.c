#include "bsp_LED.h"

void LED_init(){
	GPIO_InitTypeDef gpioinit;
	gpioinit.Mode = GPIO_OUT_PP;
	gpioinit.Pin = GPIO_Pin_3;
	GPIO_Inilize(GPIO_P5,&gpioinit);
    gpioinit.Mode = GPIO_PullUp;
	gpioinit.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P2,&gpioinit);
	gpioinit.Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Inilize(GPIO_P1,&gpioinit);
}

void OpenLed(u8 Led){
    switch (Led)
    {
        case 0: LED0 = 1; break;
        case 1: LED1 = 0; break;
        case 2: LED2 = 0; break;
        case 3: LED3 = 0; break;
        case 4: LED4 = 0; break;
        case 5: LED5 = 0; break;
        case 6: LED6 = 0; break;
        case 7: LED7 = 0; break;
        case 8: LED8 = 0; break;
        default:
            break;
    }
    
}

void CloseLEd(u8 Led){
    switch (Led)
    {
        case 0: LED0 = 0; break;
        case 1: LED1 = 1; break;
        case 2: LED2 = 1; break;
        case 3: LED3 = 1; break;
        case 4: LED4 = 1; break;
        case 5: LED5 = 1; break;
        case 6: LED6 = 1; break;
        case 7: LED7 = 1; break;
        case 8: LED8 = 1; break;
        default:
            break;
    }
}

void ToggleLed(u8 Led){
    switch (Led)
    {
        case 0: LED0 ^= 1; break;
        case 1: LED1 ^= 1; break;
        case 2: LED2 ^= 1; break;
        case 3: LED3 ^= 1; break;
        case 4: LED4 ^= 1; break;
        case 5: LED5 ^= 1; break;
        case 6: LED6 ^= 1; break;
        case 7: LED7 ^= 1; break;
        case 8: LED8 ^= 1; break;
        default:
            break;
    }
}