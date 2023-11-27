#include "bsp_KEY.H"

u8 key_num = 0;

void KEY_init(){
    P5_MODE_IO_PU(GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
}

u8 Key_GetState()
{
	unsigned char keynum = 0;
	if(KEY1==0){keynum=1;}	//һ�а��������£���־λkeynum������λ�����أ���key_loop��������
	if(KEY2==0){keynum=2;}
	if(KEY3==0){keynum=3;}
	if(KEY4==0){keynum=4;}
	return keynum;
}

void key_loop()
{
	static u8 before_state,now_state;
	before_state = now_state;
	now_state = Key_GetState();		//��ȡ������־λ
    
    /*1.һ��ʼû��������ʱbefore_state = 0,now_state = 0
      2.������1����û�ɿ�ʱ��now_state = 1,��ʱbefore_state = 0�������������κε��ж�
      3.20ms��ú����ٴα����ã�before_state = now_state = 1
      4.����1�ɿ���now_state = 0����ʱbefore_state = 1�����������һ��if�жϣ�key_keyNumber��1
    */
    
	//��һ��״̬�а������£�����״̬û�а������£�˵�����ڰ��º����ֽ׶�
    //��if(before_state == 0 && now_state == 1)�����ǰ�������˲��Ϊ�棬��־λ��1�����õ�	
	if(before_state == 1 && now_state == 0)	
	{
		key_num = 1;	//ȫ�ֱ���key_keyNumber��1��ʹ��key_return�������ظ�main����ʹ��
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
