#include "bsp_Nixie.h"

u8 code LED_TABLE[] = 
{
	// 0 	1	 2	-> 9	(索引012...9)
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,
	// 0  1. 2. -> 9.	(索引10,11,12....19)
    0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,
	// . -						(索引20,21)
	0x7F, 0xBF,
	// AbCdEFHJLPqU		(索引22,23,24....33)
	0x88,0x83,0xC6,0xA1,0x86,0x8E,0x89,0xF1,0xC7,0x8C,0x98,0xC1
};

u8 code LED_pos[] = 
{
	// 0 	1	 2	-> 9	(索引012...9)
	0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xff
};

void nixie_init(){
    GPIO_InitTypeDef	GPIO_InitStructure;
    GPIO_InitStructure.Pin  = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//初始化
}

void show_nixie(u8 a_dat,u8 b_idx){
    char i;
    for(i = 7; i >= 0; i--){ // 0点亮
        NIXIE_DI = GET_BIT_VAL(a_dat, i);
        
        // 寄存器的移位操作
        NIXIE_SCK = 0;
        NOP2();
        NIXIE_SCK = 1;
        NOP2();
    }

    // 再发数字位 （控制显示哪几个）
    // 1111 1011
    
    // 7.7.空7. 7.7.7.7.  -------------------与二级制是反向
    for(i = 7; i >= 0; i--){ // 只要不是0，就是高电平
        NIXIE_DI = GET_BIT_VAL(b_idx, i);
        
        // 寄存器的移位操作
        NIXIE_SCK = 0;
        NOP2();
        NIXIE_SCK = 1;
        NOP2();
    }
    
    // 锁存操作
    NIXIE_RCK = 0;
    NOP2();
    NIXIE_RCK = 1;
    NOP2();
}
/********************************************************************************
* @author: Qi Shang
* @brief: 数码管显示函数
* @param: 显示数字num（0~9），显示位置pos（1~8，0为不显示）
* @retval: 无
********************************************************************************/
void nixie_display(u8 num,u8 pos){
    show_nixie(LED_TABLE[num],LED_pos[pos]);
}