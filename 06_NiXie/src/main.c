#include "GPIO.h"
#include "Delay.h"
#include "bsp_Nixie.h"
#include "Timer.h"
#include "NVIC.h"


void GPIO_config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//初始化
}

void TIMER_Config(){
    TIM_InitTypeDef		TIM_InitStructure;						//结构定义

	//定时器0做16位自动重装, 中断频率为100000HZ，中断函数从P6.7取反输出50KHZ方波信号.
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 2000UL);	// 初值,指定Timer频率 1000hz (每秒执行1000次，每次1ms（周期））
																		// 不要小于367hz (2.7ms周期)
																		// 不要大于1 000 000hz 一百万 （1us周期)
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//初始化Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer0_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高)
}


void main(){
    float a = 30.88;
    GPIO_config();
    TIMER_Config();
    EA = 0;
    nixie_display(8,8);
    while (1)
    {
        nixie_display((int)a/10,1);
        nixie_display((int)a%10+10,2);
        nixie_display((int)(a*10)%10,3);
        nixie_display((int)(a*100)%10,4);        
    }
    
}