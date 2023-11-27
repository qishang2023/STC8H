#include "LED.h"

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