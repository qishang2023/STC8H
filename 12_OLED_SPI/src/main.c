//////////////////////////////////////////////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
// �о�԰����
// ���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//   �� �� ��   : main.c
//   �� �� ��   : v2.0
//   ��    ��   : HuangKai
//   ��������   : 2014-0101
//   ����޸�   :
//   ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//               ˵��:
//               ----------------------------------------------------------------
//               GND    ��Դ��
//               VCC  ��5V��3.3v��Դ
//               D0   P1^0��SCL��
//               D1   P1^1��SDA��
//               RES  ��P12
//               DC   ��P13
//               CS   ��P14
//               ----------------------------------------------------------------
//  �޸���ʷ   :
//  ��    ��   :
//  ��    ��   : HuangKai
//  �޸�����   : �����ļ�
// ��Ȩ���У�����ؾ���
// Copyright(C) �о�԰����2014/3/16
// All rights reserved
//******************************************************************************/
#include "config.h"
#include "bsp_OLED_SPI.h"
#include "bmp.h"
#include "GPIO.h"
#include "bsp_RTC.h"
#include "bsp_DHT11.H"

int main(void)
{
    float t;
    u8 h;
    u8 buf[20];
    EAXSFR();
    OLED_Init(); // ��ʼ��OLED
    Timer_init();
    bsp_I2C_init();
    DHT11_init();
    OLED_Clear();
    EA = 1;
    OLED_Clear();
    // ����clockʱ��
    clock.year   = 2023;
    clock.month  = 12;
    clock.day    = 2;
    clock.week   = 6;
    clock.hour   = 11;
    clock.minute = 48;
    clock.second = 0;
    RTC_SetTime(&clock);
    while (1) {
        OLED_Display_GB2312_string(0, 0, "����ΰ����ţ�");
        if (start_DHT11 == 1) {
            start_DHT11 = 0;
            // OLED_Clear();
            if (DHT11_get_temperature(&h, &t) == 0) {
                sprintf((char *)buf, "�¶ȣ�%.1f", t);
                OLED_Display_GB2312_string(0, 2, buf);
                sprintf((char *)buf, "ʪ�ȣ�%d%%", (int)h);
                OLED_Display_GB2312_string(0, 4, buf);
            }
            if (clock.minute <= 9 && clock.second <= 9) {
                sprintf((char *)buf, "ʱ�䣺%d:0%d:0%d\0", (int)clock.hour, (int)clock.minute, (int)clock.second);
            } else if (clock.minute <= 9) {
                sprintf((char *)buf, "ʱ�䣺%d:0%d:%d\0", (int)clock.hour, (int)clock.minute, (int)clock.second);
            } else if (clock.second <= 9) {
                sprintf((char *)buf, "ʱ�䣺%d:%d:0%d\0", (int)clock.hour, (int)clock.minute, (int)clock.second);
            } else {
                sprintf((char *)buf, "ʱ�䣺%d:%d:%d\0", (int)clock.hour, (int)clock.minute, (int)clock.second);
            }
            OLED_Display_GB2312_string(0, 6, buf);
        }
    }
}