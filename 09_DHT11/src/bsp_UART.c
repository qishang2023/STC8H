#include "bsp_UART.h"

void UART_init(){
    GPIO_InitTypeDef	GPIO_InitStructure;	
    COMx_InitDefine		COMx_InitStructure;					//结构定义

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4
    NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3    
    UART1_SW(UART1_SW_P30_P31);		

	//结构定义
    GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	//初始化
}

u8 UART_getchar(){
    u8 i,dat = 0;
    // u8 *dat=(u8 *)malloc(sizeof(u8)*20);
    if((COM1.RX_TimeOut > 0) && (--COM1.RX_TimeOut == 0))
    {            
        if(COM1.RX_Cnt > 0)
        {
            for(i=0; i<COM1.RX_Cnt; i++) {
            dat = RX1_Buffer[i]; //  1 1 1 1  0 0 0 0 -> 0xF0
            TX1_write2buff(dat);	//收到的数据原样返回
            }
        }
        COM1.RX_Cnt = 0;
    }
    return dat;
}