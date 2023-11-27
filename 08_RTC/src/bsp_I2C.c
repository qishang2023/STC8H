#include "bsp_I2C.h"

void bsp_I2C_init(){    
    I2C_InitTypeDef		I2C_InitStructure;
    P3_MODE_OUT_OD(GPIO_Pin_2 | GPIO_Pin_3);
    I2C_InitStructure.I2C_Mode      = I2C_Mode_Master;	//����ѡ��   I2C_Mode_Master, I2C_Mode_Slave
    I2C_InitStructure.I2C_Enable    = ENABLE;						//I2C����ʹ��,   ENABLE, DISABLE
    I2C_InitStructure.I2C_MS_WDTA   = DISABLE;					//����ʹ���Զ�����,  ENABLE, DISABLE
    I2C_InitStructure.I2C_Speed     = 13;								//�����ٶ�=Fosc/2/(Speed*2+4),      0~63
    // 400K = 24M / 2 / (Speed * 2 + 4):
    // 400  = 12000 / (Speed * 2 + 4)
    // Speed * 2   = 26
    I2C_Init(&I2C_InitStructure);
    NVIC_I2C_Init(I2C_Mode_Master,DISABLE,Priority_0);	//����ģʽ, I2C_Mode_Master, I2C_Mode_Slave; �ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

    I2C_SW(I2C_P33_P32);					//I2C_P14_P15,I2C_P24_P25,I2C_P33_P32
}