#include "bsp_KEY.H"

u8 key_num = 0;

void KEY_init(){
    P5_MODE_IO_PU(GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
}

u8 Key_GetState()
{
	unsigned char keynum = 0;
	if(KEY1==0){keynum=1;}	//一有按键被按下，标志位keynum立即置位并返回，给key_loop函数处理
	if(KEY2==0){keynum=2;}
	if(KEY3==0){keynum=3;}
	if(KEY4==0){keynum=4;}
	return keynum;
}

void key_loop()
{
	static u8 before_state,now_state;
	before_state = now_state;
	now_state = Key_GetState();		//获取按键标志位
    
    /*1.一开始没按键按下时before_state = 0,now_state = 0
      2.当按键1按下没松开时，now_state = 1,此时before_state = 0，不满足下面任何的判断
      3.20ms后该函数再次被调用，before_state = now_state = 1
      4.按键1松开，now_state = 0，此时before_state = 1，满足下面第一条if判断，key_keyNumber置1
    */
    
	//上一个状态有按键按下，现在状态没有按键按下，说明处于按下后松手阶段
    //若if(before_state == 0 && now_state == 1)，则是按键按下瞬间为真，标志位置1，不用等	
	if(before_state == 1 && now_state == 0)	
	{
		key_num = 1;	//全局变量key_keyNumber置1，使用key_return函数返回给main函数使用
	}
	if(before_state == 2 && now_state == 0)	
	{
		key_num = 2;
	}
	if(before_state == 3 && now_state == 0)	
	{
		key_num = 3;
	}
	if(before_state == 4 && now_state == 0)	
	{
		key_num = 4;
	}
}
