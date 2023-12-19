#include "bsp_battery.h"

void battery_init(void)
{
    ADC_InitTypeDef		ADC_InitStructure;	
	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC 通道选择时间控制 0(默认),1
	ADC_InitStructure.ADC_CsHold    = 1;		//ADC 通道选择保持时间控制 0,1(默认),2,3
	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//初始化
	ADC_PowerControl(ENABLE);				//ADC电源开关, ENABLE或DISABLE

    P0_MODE_IN_HIZ(GPIO_Pin_1);    
}

//ADC读取数据：result = Get_ADCResult(ADC_CH12);

float Battery_get_voltage() {
	u16 result = Get_ADCResult(ADC_CH9);
	float v = result * 2.5 / 4096;
	return v * 3.0;
}