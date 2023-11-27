#include "GPIO.h"
#include "Delay.h"
#include "bsp_Nixie.h"
#include "Timer.h"
#include "NVIC.h"


void GPIO_config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//��ʼ��
}

void TIMER_Config(){
    TIM_InitTypeDef		TIM_InitStructure;						//�ṹ����

	//��ʱ��0��16λ�Զ���װ, �ж�Ƶ��Ϊ100000HZ���жϺ�����P6.7ȡ�����50KHZ�����ź�.
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 2000UL);	// ��ֵ,ָ��TimerƵ�� 1000hz (ÿ��ִ��1000�Σ�ÿ��1ms�����ڣ���
																		// ��ҪС��367hz (2.7ms����)
																		// ��Ҫ����1 000 000hz һ���� ��1us����)
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//��ʼ��Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer0_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���)
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