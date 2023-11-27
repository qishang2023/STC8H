// #include "GPIO.h"
#include "bsp_Nixie.h"
#include "bsp_ADC.h"
// #include "NVIC.h"

// void GPIO_config(void) {
//     GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
//     GPIO_InitStructure.Pin  = GPIO_Pin_5;		//指定要初始化的IO,
//     GPIO_InitStructure.Mode = GPIO_HighZ;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
//     GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);//初始化
// 	GPIO_InitStructure.Pin  = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;		//指定要初始化的IO,
// 	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
// 	GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//初始化
// }

// void	ADC_config(void)
// {
// 	ADC_InitTypeDef		ADC_InitStructure;		//结构定义

// 	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
// 	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC 通道选择时间控制 0(默认),1
// 	ADC_InitStructure.ADC_CsHold    = 1;		//ADC 通道选择保持时间控制 0,1(默认),2,3
// 	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
// 	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
// 	ADC_Inilize(&ADC_InitStructure);		//初始化
// 	ADC_PowerControl(ENABLE);				//ADC电源开关, ENABLE或DISABLE
// 	NVIC_ADC_Init(DISABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
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