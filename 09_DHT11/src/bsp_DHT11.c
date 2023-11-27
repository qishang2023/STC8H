#include "bsp_DHT11.H"

u8 DHT11_start = 0;

void DHT11_init(){
    P4_MODE_OUT_OD(GPIO_Pin_6);
}

void delay1us(){
    u16 i;
    i = MAIN_Fosc / 10000000;
    while(--i);
}

u8 DHT11_read_data(u8* dat) {
	u16 count; 
	u8 i, j;
	// ����: ������������18ms
	// ��������
	DHT = 0;
	delay_ms(19);
	DHT = 1;
	count = 0;
	while(DHT == 1 && count < 25) {
		count++;
		delay1us();
	}
	if(count > 25) return 1;
	
	count = 0;
	while(DHT == 0 && count < 83) {
		count++;
		delay1us();
	}
	if(count > 83) return 2;
	
	count = 0;
	while(DHT == 1 && count < 87) {
		count++;
		delay1us();
	}
	if(count > 87) return 3;
	
	// ��ʼ��������
	for(i = 0; i < 5; i++) {
		for(j = 0; j < 8; j++) {
			dat[i] <<= 1;
			// 54us�� 23-27�ߵ�ƽ ��ʾ0
			// 54us�� 68-74�ߵ�ƽ ��ʾ1
			count = 0;
			//�ȴ���Ϊ�ߵ�ƽ
			while(DHT == 0 && count <= 54) {
				count++;
				delay1us();
			}
			if(count > 54) return 4;
			count = 0;
			// �ȴ���Ϊ�͵�ƽ
			while(DHT == 1 && count <= 74) {
				count++;
				delay1us();
			}
			if(count > 27) {
				dat[i] |= 1;
			}
		}
	}
	if(dat[0] + dat[1] + dat[2] + dat[3] != dat[4]) {
		return 5;
	}
	return 0;
}

u8 DHT11_get_temperature(u8 *humidity, float *temperature) {
	u8 dat[5];
	u8 ret;
	u8 retry = 0; 
	while((ret = DHT11_read_data(dat)) && retry < 10) {
		retry++;
	}
	
	*humidity = dat[0];// �����������
    
	*temperature = dat[2] & 0x7F;// �����������
	*temperature += (dat[3] * 0.1);//����С������
	if(dat[2] & 0x80) {
		//��ʾ����
		*temperature *= -1;
	}
	return ret;
}