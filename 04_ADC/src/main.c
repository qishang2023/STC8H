// #include "GPIO.h"
#include "bsp_Nixie.h"
#include "bsp_ADC.h"
// #include "NVIC.h"

// void GPIO_config(void) {
//     GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
//     GPIO_InitStructure.Pin  = GPIO_Pin_5;		//ָ��Ҫ��ʼ����IO,
//     GPIO_InitStructure.Mode = GPIO_HighZ;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
//     GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);//��ʼ��
// 	GPIO_InitStructure.Pin  = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;		//ָ��Ҫ��ʼ����IO,
// 	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
// 	GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//��ʼ��
// }

// void	ADC_config(void)
// {
// 	ADC_InitTypeDef		ADC_InitStructure;		//�ṹ����

// 	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
// 	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
// 	ADC_InitStructure.ADC_CsHold    = 1;		//ADC ͨ��ѡ�񱣳�ʱ����� 0,1(Ĭ��),2,3
// 	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
// 	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
// 	ADC_Inilize(&ADC_InitStructure);		//��ʼ��
// 	ADC_PowerControl(ENABLE);				//ADC��Դ����, ENABLE��DISABLE
// 	NVIC_ADC_Init(DISABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
// }

void main(){
    u16 result;
    float a,b,c;
    // GPIO_config();
    // ADC_config();
    ADC_init();
    nixie_init();
    result = Get_ADCResult(ADC_CH12);
    a = result * 2.5 / 4096;
    while (1)
    {
        result = Get_ADCResult(ADC_CH12);
        a = result * 2.5 / 4096;
        c = a * 10 / (3.3 - a);
        b = 0.0543*c*c - 3.3358*c + 53.878;
        nixie_display((int)b/10,1);
        nixie_display((int)b%10+10,2);
        nixie_display((int)(b*10)%10,3);
        nixie_display((int)(b*100)%10,4);  
    }
    
}