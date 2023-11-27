#include <STC8H.H>
#include "GPIO.h"
#include "delay.h"
#include "UART.h"
#include "NVIC.h"
#include "Switch.h"
#include "LED.h"
#include "Timer.h"

void GPIO_config(){
	GPIO_InitTypeDef gpioinit;
	gpioinit.Mode = GPIO_OUT_PP;
	gpioinit.Pin = GPIO_Pin_3;
	GPIO_Inilize(GPIO_P5,&gpioinit);
	gpioinit.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P2,&gpioinit);
	gpioinit.Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Inilize(GPIO_P1,&gpioinit);
	gpioinit.Mode = GPIO_PullUp;
	gpioinit.Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Inilize(GPIO_P3,&gpioinit);
    gpioinit.Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Inilize(GPIO_P4,&gpioinit);
}
/***************  串口初始化函数 *****************/
void	UART_config(void)
{
    COMx_InitDefine		COMx_InitStructure;					//结构定义

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4
    // COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;
    // UART_Configuration(UART2, &COMx_InitStructure);	
    NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3 
    // NVIC_UART2_Init(ENABLE,Priority_1);	   
    UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
    // UART2_SW(UART2_SW_P46_P47);
}

void TIMER_config(void) {
	TIM_InitTypeDef		TIM_InitStructure;						//结构定义

	//定时器0做16位自动重装, 中断频率为100000HZ，中断函数从P6.7取反输出50KHZ方波信号.
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000UL);	// 初值,指定Timer频率 1000hz (每秒执行1000次，每次1ms（周期））
																		// 不要小于367hz (2.7ms周期)
																		// 不要大于1 000 000hz 一百万 （1us周期)
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//初始化Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer0_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	
}



void on_uart1_recv() {
    u8 i;
    // RX_Cnt收到的数据个数（字节u8 - unsigned char）
    // 将收到的数据, 按字节逐个循环
    for(i=0; i<COM2.RX_Cnt; i++) {
        u8 dat = RX2_Buffer[i]; //  1 1 1 1  0 0 0 0 -> 0xF0
        TX1_write2buff(dat);	//收到的数据原样返回
    }
}

void main()
{

//    EAXSFR();		/* 扩展寄存器访问使能 */
    GPIO_config();
    UART_config();
    TIMER_config();

    EA = 1;

    // TX4_write2buff(0x23);	// #
    // printf("STC8H8K64U UART1 Test Programme!\r\n");	//UART1发送一个字符串
    // PrintString4("STC8H8K64U UART1 Test Programme!\r\n");	//UART1发送一个字符串
	CloseLEd(0);
	while(1)
	{

        // 超时计数
        // 一旦收到了一个字节数据，RX_TimeOut会初始化一个值（例如：5）
/*         if((COM2.RX_TimeOut > 0) && (--COM2.RX_TimeOut == 0))
        {            
            if(COM2.RX_Cnt > 0)
            {
                // 收到数据了，on_uart1_recv();
                on_uart1_recv();
				ToggleLed(0);
				ToggleLed(1);
				ToggleLed(2);
				ToggleLed(3);
				ToggleLed(4);
				ToggleLed(5);
				ToggleLed(6);
				ToggleLed(7);
				ToggleLed(8);
            }
            // 处理完数据，将数据个数清零
            COM2.RX_Cnt = 0;
        }
    	// 注意这里delay代码的位置，属于while
        delay_ms(10); */
	}
}