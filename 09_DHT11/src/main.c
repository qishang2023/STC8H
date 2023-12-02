#include "bsp_Nixie.h"
#include "bsp_Timer.h"
#include "bsp_DHT11.H"
#include "bsp_oled_SPI.h"

void main(){
    u8 humidity;
    float temperature;
    u8 OLED_P6x8Str[20];
    DHT11_init();
    Timer_init();
    nixie_init();
    OLED_Init();
    EA = 1;
    OLED_Clear();
    while (1)
    {  
       if(start_DHT111 == 1){
        DHT11_get_temperature(&humidity,&temperature);
        start_DHT111 = 0;
       }
       sprintf(OLED_P6x8Str, "T:%d.%d H:%d%%\0", (int)temperature, (int)(temperature*10)%10, (int)humidity);
       OLED_ShowString(0, 6, OLED_P6x8Str);
/*         nixie_display((int)temperature/10,1);
        nixie_display((int)temperature%10+10,2);
        nixie_display((int)(temperature*10)%10,3);
        nixie_display((int)(temperature*100)%10,4);
        nixie_display((int)humidity/10,7);
        nixie_display((int)humidity%10,8); */
    }
    

}