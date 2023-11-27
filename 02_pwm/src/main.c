#include "LED.h"
#include "GPIO.h"
#include "STC8H_PWM.h"
#include "NVIC.h"
#include "Switch.h"
#include "Delay.h"
#include "Timer.h"
#include "UART.h"



PWMx_Duty dutyA;

void GPIO_config(){
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

void	PWM_config(void)
{
    PWMx_InitDefine		PWMx_InitStructure;
		
	// 配置PWM4
    PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE2;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM_Duty    =  0;								//PWM占空比时间, 0~Period
    PWMx_InitStructure.PWM_EnoSelect  = ENO4P | ENO4N;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM4, &PWMx_InitStructure);
    PWMx_InitStructure.PWM_EnoSelect  = ENO3P | ENO3N;
    PWM_Configuration(PWM3, &PWMx_InitStructure);
    PWMx_InitStructure.PWM_EnoSelect  = ENO2P | ENO2N;
    PWM_Configuration(PWM2, &PWMx_InitStructure);
    PWMx_InitStructure.PWM_EnoSelect  = ENO1P | ENO1N;
    PWM_Configuration(PWM1, &PWMx_InitStructure);

	// 配置PWMA
    PWMx_InitStructure.PWM_Period   = (MAIN_Fosc / 1000UL) - 1;					//周期时间,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMA, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB

	// 切换PWM4选择PWM4_SW_P26_P27
    PWM4_SW(PWM4_SW_P26_P27);			//PWM4_SW_P16_P17,PWM4_SW_P26_P27,PWM4_SW_P66_P67,PWM4_SW_P34_P33
    PWM3_SW(PWM3_SW_P14_P15);
    PWM2_SW(PWM2_SW_P22_P23);
    PWM1_SW(PWM1_SW_P20_P21);

	// 初始化PWMA的中断
    NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
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

void main() {
    u8 duty_percent = 100;
    u8 direction = 1;
    u8 dat = 0,i = 0;
    EAXSFR();
    GPIO_config();
    PWM_config();
    TIMER_config();
    UART_config();

    EA = 1;

    dutyA.PWM4_Duty = PERIOD * duty_percent / 100;
    UpdatePwm(PWM4, &dutyA);
    dutyA.PWM3_Duty = PERIOD * duty_percent / 100;
    UpdatePwm(PWM3, &dutyA);
    dutyA.PWM2_Duty = PERIOD * duty_percent / 100;
    UpdatePwm(PWM2, &dutyA);
    dutyA.PWM1_Duty = PERIOD * duty_percent / 100;
    UpdatePwm(PWM1, &dutyA);

    // 0 -> 100
    while(1) {
        // duty_percent += direction;
        // // 让duty_percent一直在0-100来回往返
        // if(duty_percent >= 100) {
        //     duty_percent = 100;
        //     direction = -1;
        // } else if(duty_percent <= 0) {
        //     duty_percent = 0;
        //     direction = 1;
        // }
        // 修改PWM4的duty
        if((COM1.RX_TimeOut > 0) && (--COM1.RX_TimeOut == 0))
        {            
            if(COM1.RX_Cnt > 0)
            {
                // 收到数据了，on_uart1_recv();
				for(i=0; i<COM1.RX_Cnt; i++) {
					dat = RX1_Buffer[i]; //  1 1 1 1  0 0 0 0 -> 0xF0
					TX1_write2buff(dat);	//收到的数据原样返回
				}
            }
            // 处理完数据，将数据个数清零
            COM1.RX_Cnt = 0;
        }
        switch (dat)
        {
        case 0:duty_percent = 0; break;
        case 1:duty_percent = 25; break;
        case 2:duty_percent = 50; break;
        case 3:duty_percent = 75; break;
        case 4:duty_percent = 100; break;        
        default:break;
        }
        
        dutyA.PWM4_Duty = PERIOD * duty_percent / 100;
        UpdatePwm(PWM4, &dutyA);
        dutyA.PWM3_Duty = PERIOD * duty_percent / 100;
        UpdatePwm(PWM3, &dutyA);
        dutyA.PWM2_Duty = PERIOD * duty_percent / 100;
        UpdatePwm(PWM2, &dutyA);
        dutyA.PWM1_Duty = PERIOD * duty_percent / 100;
        UpdatePwm(PWM1, &dutyA);
				
        delay_ms(20);

    }
    
}