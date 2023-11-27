#ifndef __BSP_NIXIE_H
#define __BSP_NIXIE_H

#include "GPIO.h"
#include "NVIC.h"

#define	NIXIE_DI	P44	// ��������
#define	NIXIE_SCK	P42	// ��λ�Ĵ���
#define	NIXIE_RCK	P43	// ����Ĵ���

#define GET_BIT_VAL(byte, pos)	(byte & (1 << pos))

void show_nixie(u8 a_dat,u8 a_idx);
void nixie_display(u8 num,u8 pos);
void nixie_init();

#endif // !__BSP_NIEXIE_H

