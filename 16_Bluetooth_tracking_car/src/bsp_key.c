#include "bsp_key.h"

u8 key_num = 0;

void key_init(void)
{
    P3_MODE_IO_PU(GPIO_Pin_7);
}

u8 key_scan(){
    if (KEY1)
    {
        return 0;
    }else{
        return 1;
    }    
}

void key_loop(){
    static before,now;
    before = now;
    now = key_scan();
    if(before == 0 && now == 1){
        key_num = 1;
    }
}