#include "bsp_Timer.h"
#include "BSP_MATRIX.h"


u32 sys_time = 0;
u8 last_key_stat = 1;
void Timer_init(){
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
	NVIC_Timer0_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高
}

void Timer0_ISR_Handler (void) interrupt TMR0_VECTOR		//进中断时已经清除标志
{
    sys_time++;
    if((sys_time%20) == 0){
        matrix_loop();
    }
}