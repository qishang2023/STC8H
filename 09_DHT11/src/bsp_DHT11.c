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
	// 主机: 总线拉低至少18ms
	// 主机发起
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
	
	// 开始接收数据
	for(i = 0; i < 5; i++) {
		for(j = 0; j < 8; j++) {
			dat[i] <<= 1;
			// 54us低 23-27高电平 表示0
			// 54us低 68-74高电平 表示1
			count = 0;
			//等待变为高电平
			while(DHT == 0 && count <= 54) {
				count++;
				delay1us();
			}
			if(count > 54) return 4;
			count = 0;
			// 等待变为低电平
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
	
	*humidity = dat[0];// 获得正数部分
    
	*temperature = dat[2] & 0x7F;// 获得正数部分
	*temperature += (dat[3] * 0.1);//加上小数部分
	if(dat[2] & 0x80) {
		//表示负数
		*temperature *= -1;
	}
	return ret;
}