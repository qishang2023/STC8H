#include "bsp_RTC.h"

void RTC_SetTime(RTC_clock *clock){
    u8 write_data[NUMBER];
    //1. д���� : 53  VL 0 1 1 0 0 0 1   ===  BCD ��ʽ�洢
    write_data[0] = (( (clock->second / 10) << 4  ) & 0xF0 )  |  ( clock->second % 10 ) & 0x0F;
    //2. д��֣� 33  - 0 1 1 0 0 0 1   ===  BCD ��ʽ�洢
    write_data[1] = (( (clock->minute / 10) << 4  ) & 0xF0 )  |  ( clock->minute % 10 ) & 0x0F;
    //3. д��ʱ�� 19  - - 0 1 0 0 1 0   ===  BCD ��ʽ�洢
    write_data[2] =  (((clock->hour / 10 ) << 4 )& 0xF0)  |  (clock->hour %10 )& 0x0F;
    //4. ��ȡ�� 27 - - 0 1 0 0 1 0   ===  BCD ��ʽ�洢
    write_data[3] = (((clock->day  / 10 ) << 4 ) & 0x30) |  (clock->day  % 10 ) & 0x0F;
    //5. ��ȡ���� - - - - - 0 1 0   ===  BCD ��ʽ�洢
    write_data[4] = clock->week;
    //6. ��ȡ�� C - - 1 0 0 1 0   ===  BCD ��ʽ�洢
    write_data[5] = ((( clock->month / 10 ) << 4 ) & 0x10) | (clock->month  % 10 ) & 0x0F;
    //��������C ����ֻ�Ǽ򵥵�����������ֵ��ǳ�Ե���Ϊ������ֵ >= 2000 ���� 21���ͣ�����ʾ0 ���������Ҫ������ȡʱ��Ĺ��򱣳�һ�£�
    clock->C = clock->year >= 2000 ? 0 : 1;
    write_data[5] |=  clock->C << 7;
    //7. ��ȡ��  1 0 0 1 0 0 1 0   ===  BCD ��ʽ�洢
    write_data[6] =  ((( clock->year  % 100  / 10 ) << 4 ) & 0xF0) | (clock->year  % 10 ) & 0x0F;

    I2C_WriteNbyte(PCF8563_ADDR, PCF8563_REG_TD, write_data, NUMBER);
}

void RTC_ReadTime(RTC_clock *clock){
    u8 p [NUMBER];
    I2C_ReadNbyte(PCF8563_ADDR, PCF8563_REG_TD, p, NUMBER);
    //1. ��ȡ��  VL 0 1 1 0 0 0 1   ===  BCD ��ʽ�洢
    clock->second = (( p[0] >> 4 ) & 0x07 ) * 10 + (p[0] & 0x0F);
    //2. ��ȡ��  - 0 0 1 0 0 1 0   ===  BCD ��ʽ�洢
    clock->minute = ( (p[1] >> 4 ) & 0x07 ) * 10  + (p[1] & 0x0F);
    //3. ��ȡʱ - - 0 1 0 0 1 0   ===  BCD ��ʽ�洢
    clock->hour = (( p[2] >> 4 ) & 0x03) * 10 + (p[2] & 0x0F);
    //4. ��ȡ�� - - 0 1 0 0 1 0   ===  BCD ��ʽ�洢
    clock->day = (( p[3] >> 4 ) & 0x03 ) * 10 +  (p[3] & 0x0F);
    //5. ��ȡ���� - - - - - 0 1 0   ===  BCD ��ʽ�洢
    clock->week = p[4] & 0x07;
    //6. ��ȡ�� C - - 1 0 0 1 0   ===  BCD ��ʽ�洢
    clock->month = (( p[5] >> 4 ) & 0x01) * 10 + ( p[5] & 0x0F ) ;
    //7. ��ȡ��  1 0 0 1 0 0 1 0   ===  BCD ��ʽ�洢
    // ��ݵ�����ֽڣ�8λ��ֻ�洢����ݵĺ���λֵ��ǰ�����λֵҪ���·ݵ�C��ʲô��
    clock->year = ( ( p[6] >> 4 ) & 0x0F ) * 10 + (p[6] & 0x0F);
    clock->C = ( p[5] >> 7 ) & 0x01 ;
    // ���о���C��ֵ������19���ͻ���20���ͻ���21���͡�
    // C ��0 ����ʾ������ 21 ���ͣ� C��1 ����ʾ��22���͡�
    clock->year =  clock->C == 0 ? ( 2000 + clock->year ) : (2100 + clock->year);
}