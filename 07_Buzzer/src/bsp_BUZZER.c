#include "bsp_BUZZER.h"

u16 FREQS[] = {
	523 * 1, 587 * 1, 659 * 1, 698 * 1, 784 * 1, 880 * 1, 988 * 1, 
	523 * 2, 587 * 2, 659 * 2, 698 * 2, 784 * 2, 880 * 2, 988 * 2, 
	523 * 4, 587 * 4, 659 * 4, 698 * 4, 784 * 4, 880 * 4, 988 * 4, 
	523 * 8, 587 * 8, 659 * 8, 698 * 8, 784 * 8, 880 * 8, 988 * 8, 
};

void BUZZER_init(){    
    GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
    EAXSFR();
	GPIO_InitStructure.Pin  = GPIO_Pin_0;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);//初始化
}

void Buzzer_play(u16 note){
    u16 hz = FREQS[note - 1];
	u16 period = MAIN_Fosc / hz ;
    PWMx_InitDefine		PWMx_InitStructure;

		// PWM5
    PWMx_InitStructure.PWM_Mode    		= CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM_Duty   	 	= (int)(period * 0.005);	//PWM占空比时间, 0~Period
    PWMx_InitStructure.PWM_EnoSelect    = ENO5P;			//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM5, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

		// PWMB
    PWMx_InitStructure.PWM_Period   = period - 1;			//周期时间,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB

    PWM5_SW(PWM5_SW_P00);					//PWM5_SW_P20,PWM5_SW_P17,PWM5_SW_P00,PWM5_SW_P74

    NVIC_PWM_Init(PWMB,DISABLE,Priority_0);
}


void Buzzer_stop(){
		
    PWMx_InitDefine		PWMx_InitStructure;
    PWMx_InitStructure.PWM_MainOutEnable= DISABLE;				//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = DISABLE;				//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);				//初始化PWM,  PWMA,PWMB
}