#include "bsp_ranging.h"

static void Delay10us()		//@24.000MHz
{
	unsigned char i;
	i = 78;
	while (--i);
}

void ranging_init(){
    P4_MODE_IN_HIZ(GPIO_Pin_0);
    P1_MODE_IO_PU(GPIO_Pin_3);
    TRIG = 0;
}

float ranging_get_distance(void){
    u16 count;
    float distance;//单位：厘米
    TRIG = 1;
    Delay10us();
    TRIG = 0;
    while(!ECHO);
    count = 0;
    while(ECHO){
        Delay10us();
        count++;
    }
    printf("count = %d\r\n", count);
    //1秒343米，1ms则34.3cm，10us则0.343cm
    distance = count * 0.343 / 2.0;
    return distance;

}