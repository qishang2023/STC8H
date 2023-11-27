#include "bsp_Timer.h"
#include "BSP_MATRIX.h"


u32 sys_time = 0;
u8 last_key_stat = 1;
void Timer_init(){
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
	NVIC_Timer0_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���
}

void Timer0_ISR_Handler (void) interrupt TMR0_VECTOR		//���ж�ʱ�Ѿ������־
{
    sys_time++;
    if((sys_time%20) == 0){
        matrix_loop();
    }
}