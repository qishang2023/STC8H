/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

#include	"STC8G_PWM15bit.h"

//========================================================================
// ����: PWM0_ISR_Handler
// ����: 15λ��ǿ��PWM0�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-23
//========================================================================
void	PWM0_ISR_Handler (void) interrupt PWM0_VECTOR
{
	if(PWMCFG01 & 0x08)		//PWM0�������ж�
	{
		PWMCFG01 &= ~0x08;		//��PWM0�������жϱ�־
		// TODO: �ڴ˴������û�����
	}
	if(PWM0IF)		//PWM0ƥ���ж�
	{
		PWM0IF = 0;
		// TODO: �ڴ˴������û�����
	}
}

//========================================================================
// ����: PWM1_ISR_Handler
// ����: 15λ��ǿ��PWM1�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-23
//========================================================================
void	PWM1_ISR_Handler (void) interrupt PWM1_VECTOR
{
	if(PWMCFG01 & 0x80)		//PWM1�������ж�
	{
		PWMCFG01 &= ~0x80;		//��PWM1�������жϱ�־
		// TODO: �ڴ˴������û�����
	}
	if(PWM1IF)		//PWM1ƥ���ж�
	{
		PWM1IF = 0;
		// TODO: �ڴ˴������û�����
	}
}

//========================================================================
// ����: PWM2_ISR_Handler
// ����: 15λ��ǿ��PWM2�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-23
//========================================================================
void	PWM2_ISR_Handler (void) interrupt PWM2_VECTOR
{
	if(PWMCFG23 & 0x08)		//PWM2�������ж�
	{
		PWMCFG23 &= ~0x08;		//��PWM2�������жϱ�־
		// TODO: �ڴ˴������û�����
	}
	if(PWM2IF)		//PWM2ƥ���ж�
	{
		PWM2IF = 0;
		// TODO: �ڴ˴������û�����
	}
}

//========================================================================
// ����: PWM3_ISR_Handler
// ����: 15λ��ǿ��PWM3�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-23
//========================================================================
void	PWM3_ISR_Handler (void) interrupt PWM3_VECTOR
{
	if(PWMCFG23 & 0x80)		//PWM3�������ж�
	{
		PWMCFG23 &= ~0x80;		//��PWM3�������жϱ�־
		// TODO: �ڴ˴������û�����
	}
	if(PWM3IF)		//PWM3ƥ���ж�
	{
		PWM3IF = 0;
		// TODO: �ڴ˴������û�����
	}
}

//========================================================================
// ����: PWM4_ISR_Handler
// ����: 15λ��ǿ��PWM4�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-23
//========================================================================
void	PWM4_ISR_Handler (void) interrupt PWM4_VECTOR
{
	if(PWMCFG45 & 0x08)		//PWM4�������ж�
	{
		PWMCFG45 &= ~0x08;		//��PWM4�������жϱ�־
		// TODO: �ڴ˴������û�����
	}
	if(PWM4IF)		//PWM4ƥ���ж�
	{
		PWM4IF = 0;
		// TODO: �ڴ˴������û�����
	}
}

//========================================================================
// ����: PWM5_ISR_Handler
// ����: 15λ��ǿ��PWM5�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-23
//========================================================================
//void	PWM5_ISR_Handler (void) interrupt PWM5_VECTOR	//�ж������ų���31���ɽ��������жϺ���ת�����������������
//{
//	if(PWMCFG45 & 0x80)		//PWM5�������ж�
//	{
//		PWMCFG45 &= ~0x80;		//��PWM5�������жϱ�־
//		// TODO: �ڴ˴������û�����
//	}
//}