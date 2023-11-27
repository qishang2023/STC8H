#include "bsp_Nixie.h"
#include "bsp_Timer.h"
#include "bsp_DHT11.H"

void main(){
    u8 humidity;
    float temperature;
    DHT11_init();
    Timer_init();
    nixie_init();
    EA = 1;

    while (1)
    {  
       if(start_DHT111 == 1){
        DHT11_get_temperature(&humidity,&temperature);
        start_DHT111 = 0;
       }
        nixie_display((int)temperature/10,1);
        nixie_display((int)temperature%10+10,2);
        nixie_display((int)(temperature*10)%10,3);
        nixie_display((int)(temperature*100)%10,4);
        nixie_display((int)humidity/10,7);
        nixie_display((int)humidity%10,8);
    }
    

}