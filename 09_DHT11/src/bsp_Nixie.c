#include "bsp_Nixie.h"

u8 code LED_TABLE[] = 
{
	// 0 	1	 2	-> 9	(����012...9)
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,
	// 0  1. 2. -> 9.	(����10,11,12....19)
    0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,
	// . -						(����20,21)
	0x7F, 0xBF,
	// AbCdEFHJLPqU		(����22,23,24....33)
	0x88,0x83,0xC6,0xA1,0x86,0x8E,0x89,0xF1,0xC7,0x8C,0x98,0xC1
};

u8 code LED_pos[] = 
{
	// 0 	1	 2	-> 9	(����012...9)
	0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xff
};

void nixie_init(){
    GPIO_InitTypeDef	GPIO_InitStructure;
    GPIO_InitStructure.Pin  = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//��ʼ��
}

void show_nixie(u8 a_dat,u8 b_idx){
    char i;
    for(i = 7; i >= 0; i--){ // 0����
        NIXIE_DI = GET_BIT_VAL(a_dat, i);
        
        // �Ĵ�������λ����
        NIXIE_SCK = 0;
        NOP2();
        NIXIE_SCK = 1;
        NOP2();
    }

    // �ٷ�����λ ��������ʾ�ļ�����
    // 1111 1011
    
    // 7.7.��7. 7.7.7.7.  -------------------��������Ƿ���
    for(i = 7; i >= 0; i--){ // ֻҪ����0�����Ǹߵ�ƽ
        NIXIE_DI = GET_BIT_VAL(b_idx, i);
        
        // �Ĵ�������λ����
        NIXIE_SCK = 0;
        NOP2();
        NIXIE_SCK = 1;
        NOP2();
    }
    
    // �������
    NIXIE_RCK = 0;
    NOP2();
    NIXIE_RCK = 1;
    NOP2();
}
/********************************************************************************
* @author: Qi Shang
* @brief: �������ʾ����
* @param: ��ʾ����num��0~9������ʾλ��pos��1~8��0Ϊ����ʾ��
* @retval: ��
********************************************************************************/
void nixie_display(u8 num,u8 pos){
    show_nixie(LED_TABLE[num],LED_pos[pos]);
}