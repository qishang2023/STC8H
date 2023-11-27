#include "bsp_PWM.h"

void PWM_init(){    
    GPIO_InitTypeDef init;
    PWMx_InitDefine  PWMx_InitStructure;
    EAXSFR();
    init.Mode = GPIO_OUT_PP;
    init.Pin = GPIO_Pin_1;
    GPIO_Inilize(GPIO_P0,&init);

    PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM_Duty    =  0;								//PWM占空比时间, 0~Period
    PWMx_InitStructure.PWM_EnoSelect  = ENO6P;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM6, &PWMx_InitStructure);

	// 配置PWMA
    PWMx_InitStructure.PWM_Period   = PERIOD - 1;					//周期时间,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB

	// 切换PWM4选择PWM4_SW_P26_P27
    PWM6_SW(PWM6_SW_P01);			//PWM4_SW_P16_P17,PWM4_SW_P26_P27,PWM4_SW_P66_P67,PWM4_SW_P34_P33

	// 初始化PWMA的中断
    NVIC_PWM_Init(PWMB,DISABLE,Priority_0);
}

void PWM_set(u8 duty_percent){
    PWMx_Duty dutyA;
    dutyA.PWM6_Duty = PERIOD * duty_percent / 100;
    UpdatePwm(PWM6, &dutyA);
}