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
		
	// ����PWM4
    PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE2;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM_Duty    =  0;								//PWMռ�ձ�ʱ��, 0~Period
    PWMx_InitStructure.PWM_EnoSelect  = ENO4P | ENO4N;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM4, &PWMx_InitStructure);
    PWMx_InitStructure.PWM_EnoSelect  = ENO3P | ENO3N;
    PWM_Configuration(PWM3, &PWMx_InitStructure);
    PWMx_InitStructure.PWM_EnoSelect  = ENO2P | ENO2N;
    PWM_Configuration(PWM2, &PWMx_InitStructure);
    PWMx_InitStructure.PWM_EnoSelect  = ENO1P | ENO1N;
    PWM_Configuration(PWM1, &PWMx_InitStructure);

	// ����PWMA
    PWMx_InitStructure.PWM_Period   = (MAIN_Fosc / 1000UL) - 1;					//����ʱ��,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//��������������, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//�����ʹ��, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//ʹ�ܼ�����, ENABLE,DISABLE
    PWM_Configuration(PWMA, &PWMx_InitStructure);			//��ʼ��PWMͨ�üĴ���,  PWMA,PWMB

	// �л�PWM4ѡ��PWM4_SW_P26_P27
    PWM4_SW(PWM4_SW_P26_P27);			//PWM4_SW_P16_P17,PWM4_SW_P26_P27,PWM4_SW_P66_P67,PWM4_SW_P34_P33
    PWM3_SW(PWM3_SW_P14_P15);
    PWM2_SW(PWM2_SW_P22_P23);
    PWM1_SW(PWM1_SW_P20_P21);

	// ��ʼ��PWMA���ж�
    NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
}

void TIMER_config(void) {
	TIM_InitTypeDef		TIM_InitStructure;						//�ṹ����

	//��ʱ��0��16λ�Զ���װ, �ж�Ƶ��Ϊ100000HZ���жϺ�����P6.7ȡ�����50KHZ�����ź�.
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000UL);	// ��ֵ,ָ��TimerƵ�� 1000hz (ÿ��ִ��1000�Σ�ÿ��1ms�����ڣ���
																		// ��ҪС��367hz (2.7ms����)
																		// ��Ҫ����1 000 000hz һ���� ��1us����)
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//��ʼ��Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer0_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	
}

void	UART_config(void)
{
    COMx_InitDefine		COMx_InitStructure;					//�ṹ����

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4
    // COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;
    // UART_Configuration(UART2, &COMx_InitStructure);	
    NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3 
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
        // // ��duty_percentһֱ��0-100��������
        // if(duty_percent >= 100) {
        //     duty_percent = 100;
        //     direction = -1;
        // } else if(duty_percent <= 0) {
        //     duty_percent = 0;
        //     direction = 1;
        // }
        // �޸�PWM4��duty
        if((COM1.RX_TimeOut > 0) && (--COM1.RX_TimeOut == 0))
        {            
            if(COM1.RX_Cnt > 0)
            {
                // �յ������ˣ�on_uart1_recv();
				for(i=0; i<COM1.RX_Cnt; i++) {
					dat = RX1_Buffer[i]; //  1 1 1 1  0 0 0 0 -> 0xF0
					TX1_write2buff(dat);	//�յ�������ԭ������
				}
            }
            // ���������ݣ������ݸ�������
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