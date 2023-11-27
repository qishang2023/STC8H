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
/***************  ���ڳ�ʼ������ *****************/
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



void on_uart1_recv() {
    u8 i;
    // RX_Cnt�յ������ݸ������ֽ�u8 - unsigned char��
    // ���յ�������, ���ֽ����ѭ��
    for(i=0; i<COM2.RX_Cnt; i++) {
        u8 dat = RX2_Buffer[i]; //  1 1 1 1  0 0 0 0 -> 0xF0
        TX1_write2buff(dat);	//�յ�������ԭ������
    }
}

void main()
{

//    EAXSFR();		/* ��չ�Ĵ�������ʹ�� */
    GPIO_config();
    UART_config();
    TIMER_config();

    EA = 1;

    // TX4_write2buff(0x23);	// #
    // printf("STC8H8K64U UART1 Test Programme!\r\n");	//UART1����һ���ַ���
    // PrintString4("STC8H8K64U UART1 Test Programme!\r\n");	//UART1����һ���ַ���
	CloseLEd(0);
	while(1)
	{

        // ��ʱ����
        // һ���յ���һ���ֽ����ݣ�RX_TimeOut���ʼ��һ��ֵ�����磺5��
/*         if((COM2.RX_TimeOut > 0) && (--COM2.RX_TimeOut == 0))
        {            
            if(COM2.RX_Cnt > 0)
            {
                // �յ������ˣ�on_uart1_recv();
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
            // ���������ݣ������ݸ�������
            COM2.RX_Cnt = 0;
        }
    	// ע������delay�����λ�ã�����while
        delay_ms(10); */
	}
}