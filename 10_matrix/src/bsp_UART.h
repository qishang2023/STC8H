#ifndef __BSP_UART_H
#define __BSP_UART_H

#include "GPIO.h"
#include "NVIC.h"
#include "Switch.h"
#include "UART.h"

void UART_init();
u8 UART_getchar();

#endif // !__BSP_UART_H