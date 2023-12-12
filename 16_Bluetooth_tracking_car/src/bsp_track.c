#include "bsp_track.h"

u8 track_state = 0;

void track_init(void)
{
    P0_MODE_IO_PU(GPIO_Pin_6);
    P3_MODE_IO_PU(GPIO_Pin_2 | GPIO_Pin_3);
    P4_MODE_IO_PU(GPIO_Pin_7);
    P5_MODE_IO_PU(GPIO_Pin_0);
}

void trcak_get_state(void)
{
    track_state = 0;
    if(TRACK_R == 0)
    {
        track_state |= 0x01;
    }
    if(TRACK_MR == 0)
    {
        track_state |= 0x02;
    }
    if(TRACK_M == 0)
    {
        track_state |= 0x04;
    }
    if(TRACK_ML == 0)
    {
        track_state |= 0x08;
    }
    if(TRACK_L == 0)
    {
        track_state |= 0x10;
    }
}

int Track_get_position(){
	 // �������ѹ���ߵĵƵ�ƽ����
	int sum = 0, count = 0, pos = 0;
	// static ֻ���ʼ��һ��
	static int last_pos = 0;
	
	if(TRACK_R == 1){
		sum += 64;
		count ++;
	}
	
	if(TRACK_MR == 1){
		sum += 32;
		count ++;
	}
	
	if(TRACK_M == 1){
		sum += 0;
		count ++;
	}
	
	if(TRACK_ML == 1){
		sum += -32;
		count ++;
	}
	
	if(TRACK_L == 1){
		sum += -64;
		count ++;
	}
	
	if(count == 0){
		return last_pos;// ��һ�ε�pos
	}
	
	pos = sum / count;
	
	// �ѵ�ǰ���µ�ֵ��¼����,������һ��ûѹ���ߵ�ʱ��,����
	last_pos = pos;
	
	return pos;
}