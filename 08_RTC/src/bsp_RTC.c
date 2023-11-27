#include "bsp_RTC.h"

void RTC_SetTime(RTC_clock *clock){
    u8 write_data[NUMBER];
    //1. 写入秒 : 53  VL 0 1 1 0 0 0 1   ===  BCD 格式存储
    write_data[0] = (( (clock->second / 10) << 4  ) & 0xF0 )  |  ( clock->second % 10 ) & 0x0F;
    //2. 写入分： 33  - 0 1 1 0 0 0 1   ===  BCD 格式存储
    write_data[1] = (( (clock->minute / 10) << 4  ) & 0xF0 )  |  ( clock->minute % 10 ) & 0x0F;
    //3. 写入时： 19  - - 0 1 0 0 1 0   ===  BCD 格式存储
    write_data[2] =  (((clock->hour / 10 ) << 4 )& 0xF0)  |  (clock->hour %10 )& 0x0F;
    //4. 读取日 27 - - 0 1 0 0 1 0   ===  BCD 格式存储
    write_data[3] = (((clock->day  / 10 ) << 4 ) & 0x30) |  (clock->day  % 10 ) & 0x0F;
    //5. 读取星期 - - - - - 0 1 0   ===  BCD 格式存储
    write_data[4] = clock->week;
    //6. 读取月 C - - 1 0 0 1 0   ===  BCD 格式存储
    write_data[5] = ((( clock->month / 10 ) << 4 ) & 0x10) | (clock->month  % 10 ) & 0x0F;
    //设置世纪C 这里只是简单的设置了世纪值，浅显的认为如果年份值 >= 2000 就是 21世纪，即表示0 。这个规则要和下面取时间的规则保持一致！
    clock->C = clock->year >= 2000 ? 0 : 1;
    write_data[5] |=  clock->C << 7;
    //7. 读取年  1 0 0 1 0 0 1 0   ===  BCD 格式存储
    write_data[6] =  ((( clock->year  % 100  / 10 ) << 4 ) & 0xF0) | (clock->year  % 10 ) & 0x0F;

    I2C_WriteNbyte(PCF8563_ADDR, PCF8563_REG_TD, write_data, NUMBER);
}

void RTC_ReadTime(RTC_clock *clock){
    u8 p [NUMBER];
    I2C_ReadNbyte(PCF8563_ADDR, PCF8563_REG_TD, p, NUMBER);
    //1. 读取秒  VL 0 1 1 0 0 0 1   ===  BCD 格式存储
    clock->second = (( p[0] >> 4 ) & 0x07 ) * 10 + (p[0] & 0x0F);
    //2. 读取分  - 0 0 1 0 0 1 0   ===  BCD 格式存储
    clock->minute = ( (p[1] >> 4 ) & 0x07 ) * 10  + (p[1] & 0x0F);
    //3. 读取时 - - 0 1 0 0 1 0   ===  BCD 格式存储
    clock->hour = (( p[2] >> 4 ) & 0x03) * 10 + (p[2] & 0x0F);
    //4. 读取日 - - 0 1 0 0 1 0   ===  BCD 格式存储
    clock->day = (( p[3] >> 4 ) & 0x03 ) * 10 +  (p[3] & 0x0F);
    //5. 读取星期 - - - - - 0 1 0   ===  BCD 格式存储
    clock->week = p[4] & 0x07;
    //6. 读取月 C - - 1 0 0 1 0   ===  BCD 格式存储
    clock->month = (( p[5] >> 4 ) & 0x01) * 10 + ( p[5] & 0x0F ) ;
    //7. 读取年  1 0 0 1 0 0 1 0   ===  BCD 格式存储
    // 年份的这个字节（8位）只存储了年份的后两位值，前面的两位值要看月份的C是什么。
    clock->year = ( ( p[6] >> 4 ) & 0x0F ) * 10 + (p[6] & 0x0F);
    clock->C = ( p[5] >> 7 ) & 0x01 ;
    // 自行决定C的值到底是19世纪还是20世纪还是21世纪。
    // C 是0 即表示现在是 21 世纪， C是1 即表示是22世纪。
    clock->year =  clock->C == 0 ? ( 2000 + clock->year ) : (2100 + clock->year);
}