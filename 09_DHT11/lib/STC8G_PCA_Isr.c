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

#include	"STC8G_PCA.h"

//========================================================================
//                               ���ر�������
//========================================================================

u16		CAP0_Old,CAP1_Old,CAP2_Old;       //��¼��һ�εĲ���ֵ
u16		CAP0_New,CAP1_New,CAP2_New;       //��¼���εĲ���ֵ

//========================================================================
// ����: PCA_ISR_Handler
// ����: PCA�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-23
//========================================================================
void	PCA_ISR_Handler (void) interrupt PCA_VECTOR
{
	if(CCF0)		//PCAģ��0�ж�
	{
		CCF0 = 0;		//��PCAģ��0�жϱ�־
		// TODO: �ڴ˴�����û�����
		if(CCAPM0 >= PCA_Mode_SoftTimer)		//PCA_Mode_SoftTimer and PCA_Mode_HighPulseOutput
		{
			CCAP0_tmp += PCA_Timer0;
			CCAP0L = (u8)CCAP0_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
			CCAP0H = (u8)(CCAP0_tmp >> 8);	//��дCCAP0H
		}
		else if(CCAPM0 & PCA_Mode_Capture)
		{
			CAP0_Old = CAP0_New;
			CAP0_New = CCAP0H;	//��CCAP0H
			CAP0_New = (CAP0_New << 8) + CCAP0L;
			CCAP0_tmp = CAP0_New - CAP0_Old;
			B_Capture0 = 1;
		}
	}

	if(CCF1)	//PCAģ��1�ж�
	{
		CCF1 = 0;		//��PCAģ��1�жϱ�־
		// TODO: �ڴ˴�����û�����
		if(CCAPM1 >= PCA_Mode_SoftTimer)		//PCA_Mode_SoftTimer and PCA_Mode_HighPulseOutput
		{
			CCAP1_tmp += PCA_Timer1;
			CCAP1L = (u8)CCAP1_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
			CCAP1H = (u8)(CCAP1_tmp >> 8);	//��дCCAP0H
		}
		else if(CCAPM1 & PCA_Mode_Capture)
		{
			CAP1_Old = CAP1_New;
			CAP1_New = CCAP1H;	//��CCAP1H
			CAP1_New = (CAP1_New << 8) + CCAP1L;
			CCAP1_tmp = CAP1_New - CAP1_Old;
			B_Capture1 = 1;
		}
	}

	if(CCF2)	//PCAģ��2�ж�
	{
		CCF2 = 0;		//��PCAģ��1�жϱ�־
		// TODO: �ڴ˴�����û�����
		if(CCAPM2 >= PCA_Mode_SoftTimer)		//PCA_Mode_SoftTimer and PCA_Mode_HighPulseOutput
		{
			CCAP2_tmp += PCA_Timer2;
			CCAP2L = (u8)CCAP2_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
			CCAP2H = (u8)(CCAP2_tmp >> 8);	//��дCCAP0H
		}
		else if(CCAPM2 & PCA_Mode_Capture)
		{
			CAP2_Old = CAP2_New;
			CAP2_New = CCAP2H;	//��CCAP2H
			CAP2_New = (CAP2_New << 8) + CCAP2L;
			CCAP2_tmp = CAP2_New - CAP2_Old;
			B_Capture2 = 1;
		}
	}

	if(CF)	//PCA����ж�
	{
		CF = 0;			//��PCA����жϱ�־
		// TODO: �ڴ˴�����û�����
	}

}