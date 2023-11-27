#include "bsp_Nixie.h"
#include "bsp_UART.h"
#include "bsp_I2C.h"
#include "Delay.h"
#include "bsp_Timer.h"

extern u8 dat[7];

void main(){
 // �豸��ַ read A3h and write A2h
    u8 dev_addr = 0x51 << 1; 	// (�豸��ַ << 1) | 0 = д��ַ. 
    // �洢��ַ
    u8 mem_addr = 0x02;
    // ���ڽ��մӻ�����������
    u8 tem[7]={0x50,0x35,0x21,0x31,0x00,0x92,0x23};
	// ����ʱ����Ϣ
    // u8 second, minute, hour, day, week, month;
    // u16 year;

    // ������չ�Ĵ���ʹ��
    EAXSFR();

    bsp_I2C_init();
    UART_init();
    nixie_init();
    Timer_init();

    EA = 1;

//		4. ͨ��I2C��RTCʱ��оƬд����
    I2C_WriteNbyte(dev_addr, mem_addr, tem, 7);

    printf("--------------------------------read\n");
    while(1) {

		//		3. ͨ��I2C��ȡRTCʱ��оƬ����
        // I2C_ReadNbyte(dev_addr, mem_addr, &dat, 7);
        // second = (dat[0] & 0x0F) + ((dat[0] >> 4) & 0x07) * 10;
        // minute = (dat[1] & 0x0F) + ((dat[1] >> 4) & 0x07) * 10;
        // hour = (dat[2] & 0x0F) + ((dat[2] >> 4) & 0x03) * 10;
        // day = (dat[3] & 0x0F) + ((dat[3] >> 4) & 0x03) * 10;
        // week = dat[4] & 0x07;
        // month = (dat[5] & 0x0F) + ((dat[5] >> 4) & 0x01) * 10;
        // year = ((dat[6] >> 4) & 0x0F) * 10 + (dat[6] & 0x0F);
        // year += ((dat[5] >> 7) & 0x01) * 100 + 1900;

        nixie_display((int)(dat[2] >> 4),1);
        nixie_display((int)(dat[2] & 0x0F),2);
        nixie_display(21,3);
        nixie_display((int)(dat[1] >> 4),4);
        nixie_display((int)(dat[1] & 0x0F),5); 
        nixie_display(21,6); 
        nixie_display((int)(dat[0] >> 4),7); 
        nixie_display((int)(dat[0] & 0x0F),8); 

        // printf("%d:%d:%d \n", (int)year, (int)month, (int)day);
        // printf("%d:%d:%d \n", (int)hour, (int)minute, (int)second);
    
        // delay_ms(250);
        // delay_ms(250);
        // delay_ms(250);
        // delay_ms(250);
    }
}