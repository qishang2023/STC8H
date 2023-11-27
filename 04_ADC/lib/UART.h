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

#ifndef __UART_H
#define __UART_H	 

#include	"config.h"

//========================================================================
//                              ��������
//========================================================================

#define	UART1	1       //ʹ����Щ���ھͿ���Ӧ�Ķ��壬���õĴ��ڿ����ε����壬��ʡ��Դ
// #define	UART2	2
// #define	UART3	3
// #define	UART4	4

#define	UART_QUEUE_MODE	0           //���ô��ڷ���ģʽ��0������ģʽ��1������ģʽ

#define	PRINTF_SELECT  UART1		//ѡ�� printf ������ʹ�õĴ��ڣ����� UART1~UART4

#ifdef UART1
#define	COM_TX1_Lenth	128
#define	COM_RX1_Lenth	128
#endif
#ifdef UART2
#define	COM_TX2_Lenth	128
#define	COM_RX2_Lenth	128
#endif
#ifdef UART3
#define	COM_TX3_Lenth	64
#define	COM_RX3_Lenth	64
#endif
#ifdef UART4
#define	COM_TX4_Lenth	32
#define	COM_RX4_Lenth	32
#endif

#define	UART_ShiftRight	0		//ͬ����λ���
#define	UART_8bit_BRTx	(1<<6)	//8λ����,�ɱ䲨����
#define	UART_9bit		(2<<6)	//9λ����,�̶�������
#define	UART_9bit_BRTx	(3<<6)	//9λ����,�ɱ䲨����

#define	TimeOutSet1		5
#define	TimeOutSet2		5
#define	TimeOutSet3		5
#define	TimeOutSet4		5

#define	BRT_Timer1	1
#define	BRT_Timer2	2
#define	BRT_Timer3	3
#define	BRT_Timer4	4

//========================================================================
//                              UART����
//========================================================================

#define		TI2					(S2CON & 2) 		/* �ж�TI2�Ƿ������ */
#define		RI2					(S2CON & 1) 		/* �ж�RI2�Ƿ������� */
#define		SET_TI2()			S2CON |=  (1<<1)	/* ����TI2(�����ж�) */
#define		CLR_TI2()			S2CON &= ~(1<<1)	/* ���TI2 */
#define		CLR_RI2()			S2CON &= ~1			/* ���RI2 */

#define		TI3					(S3CON & 2) != 0	/* �ж�TI3�Ƿ������ */
#define		RI3					(S3CON & 1) != 0	/* �ж�RI3�Ƿ������� */
#define		SET_TI3()			S3CON |=  (1<<1)	/* ����TI3(�����ж�) */
#define		CLR_TI3()			S3CON &= ~(1<<1)	/* ���TI3 */
#define		CLR_RI3()			S3CON &= ~1			/* ���RI3 */

#define		TI4					(S4CON & 2) != 0	/* �ж�TI3�Ƿ������ */
#define		RI4					(S4CON & 1) != 0	/* �ж�RI3�Ƿ������� */
#define		SET_TI4()			S4CON |=  2			/* ����TI3(�����ж�) */
#define		CLR_TI4()			S4CON &= ~2			/* ���TI3 */
#define		CLR_RI4()			S4CON &= ~1			/* ���RI3 */

#define		UART1_RxEnable(n)	(n==0?(REN = 0):(REN = 1))			/* UART1����ʹ�� */
#define		UART2_RxEnable(n)	S2CON = (S2CON & ~0x10) | (n << 4)	/* UART2����ʹ�� */
#define		UART3_RxEnable(n)	S3CON = (S3CON & ~0x10) | (n << 4)	/* UART3����ʹ�� */
#define		UART4_RxEnable(n)	S4CON = (S4CON & ~0x10) | (n << 4)	/* UART4����ʹ�� */

typedef struct
{ 
	u8	TX_send;		//�ѷ���ָ��
	u8	TX_write;		//����дָ��
	u8	B_TX_busy;		//æ��־

	u8 	RX_Cnt;			//�����ֽڼ���
	u8	RX_TimeOut;		//���ճ�ʱ
} COMx_Define; 

typedef struct
{ 
	u8	UART_Mode;			//ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	u8	UART_BRT_Use;		//ʹ�ò�����,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	u32	UART_BaudRate;		//������, 	   һ�� 110 ~ 115200
	u8	Morecommunicate;	//���ͨѶ����, ENABLE,DISABLE
	u8	UART_RxEnable;		//�������,   ENABLE,DISABLE
	u8	BaudRateDouble;		//�����ʼӱ�, ENABLE,DISABLE
} COMx_InitDefine; 

#ifdef UART1
extern	COMx_Define	COM1;
extern	u8	xdata TX1_Buffer[COM_TX1_Lenth];	//���ͻ���
extern	u8 	xdata RX1_Buffer[COM_RX1_Lenth];	//���ջ���
#endif
#ifdef UART2
extern	COMx_Define	COM2;
extern	u8	xdata TX2_Buffer[COM_TX2_Lenth];	//���ͻ���
extern	u8 	xdata RX2_Buffer[COM_RX2_Lenth];	//���ջ���
#endif
#ifdef UART3
extern	COMx_Define	COM3;
extern	u8	xdata TX3_Buffer[COM_TX3_Lenth];	//���ͻ���
extern	u8 	xdata RX3_Buffer[COM_RX3_Lenth];	//���ջ���
#endif
#ifdef UART4
extern	COMx_Define	COM4;
extern	u8	xdata TX4_Buffer[COM_TX4_Lenth];	//���ͻ���
extern	u8 	xdata RX4_Buffer[COM_RX4_Lenth];	//���ջ���
#endif

u8	UART_Configuration(u8 UARTx, COMx_InitDefine *COMx);
#ifdef UART1
void TX1_write2buff(u8 dat);	//����1���ͺ���
void PrintString1(u8 *puts);
#endif
#ifdef UART2
void TX2_write2buff(u8 dat);	//����2���ͺ���
void PrintString2(u8 *puts);
#endif
#ifdef UART3
void TX3_write2buff(u8 dat);	//����3���ͺ���
void PrintString3(u8 *puts);
#endif
#ifdef UART4
void TX4_write2buff(u8 dat);	//����4���ͺ���
void PrintString4(u8 *puts);
#endif

//void COMx_write2buff(u8 UARTx, u8 dat);	//���ڷ��ͺ���
//void PrintString(u8 UARTx, u8 *puts);

#endif

