#include "RTX51TNY.H"
#include "bsp_track.h"
#include "bsp_light.h"
#include "UART.h"
#include "NVIC.h"
#include "Switch.h"
#include "bsp_key.h"
#include "bsp_battery.h"
#include "bsp_ranging.h"
#include "bsp_motor.h"
#include "bsp_buzzer.h"

void UART_init()
{
    COMx_InitDefine COMx_InitStructure; // �ṹ����

    P1_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx; // ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;     // ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;       // ������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;         // ��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;        // �����ʼӱ�, ENABLE��DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);     // ��ʼ������1 UART1,UART2,UART3,UART4
    NVIC_UART1_Init(ENABLE, Priority_1);                // �ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    UART1_SW(UART1_SW_P30_P31);

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx; // ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;     // ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 9600ul;         // ������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;         // ��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;        // �����ʼӱ�, ENABLE��DISABLE
    UART_Configuration(UART2, &COMx_InitStructure);     // ��ʼ������1 UART1,UART2,UART3,UART4

    NVIC_UART2_Init(ENABLE, Priority_1); // �ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    UART2_SW(UART2_SW_P10_P11);          // ����ѡ��, UART2_SW_P10_P11,UART2_SW_P46_P47
}

void do_control() _task_ 4
{
    // float distance;
    int pos, last_pos;
    buzzer_beep();
    while (1) {
        pos      = Track_get_position();
        // distance = ranging_get_distance();
        // if (distance < 30) {
        //     Motors_stop();
        //     buzzer_beep();
        //     os_wait2(K_TMO, 2);
        //     buzzer_beep();
        //     os_wait2(K_TMO, 2);
        //     buzzer_beep();
        //     continue;
        // }
        // �ϴε�pos�ͱ���pos��ͬ, ��������ѭ��, ����Ƶ������ͬ��PWM
        if (last_pos == pos) {
            os_wait2(K_TMO, 2); // 5ms * 2 = 10ms
            continue;
        }
        // pos Ϊ��ֵ -> ��ת, Ϊ��ֵ -> ��ת
        if (pos < 0 ) {
            Motor_left(10);
        } else if (pos > 0 ) {
            Motor_right(10);
        } /*else if (pos <= 0 && last_pos > 0) {
            Motor_left(10);
        } else if (pos >= 0 && last_pos < 0) {
            Motor_right(10);
        } */else {
            Motors_forward(15);
        }
        last_pos = pos;
        os_wait2(K_TMO, 4);
    }
}

void sys_init()
{
    EAXSFR();
    light_init();
    track_init();
    UART_init();
    key_init();
    ranging_init();
    motor_init();
    battery_init();
    buzzer_init();
}

void start_main() _task_ 0
{
    sys_init();
    // os_create_task(1);
    // os_create_task(2);
    os_create_task(3);
    os_delete_task(0);
}

void light() _task_ 1
{
    u8 mode = 4;
    while (1) {
        if (key_num) {
            key_num = 0;
            // printf("distance = %.2fCM", distance);
            switch (mode) {
                case 4:
                    Motors_around(10);
                    break;
                default:
                    Motors_stop();
                    break;
            }
            mode++;
            if (mode > 5) {
                mode = 4;
            }
            light_toggle(2);
        }
    }
}

void key() _task_ 2
{
    while (1) {
        key_loop();
        trcak_get_state();
        os_wait2(K_TMO, 8);
    }
}

void task_uart1() _task_ 3
{
    u8 i;
    while (1) {
        if (COM2.RX_TimeOut > 0) {
            if (--COM2.RX_TimeOut == 0) {
                if (COM2.RX_Cnt > 0) {
                    if (RX2_Buffer[0] == 0x55) {
                        os_create_task(4);
                    } else {
                        buzzer_beep();
                        os_delete_task(4);
                        Motors_stop();
                    }
                    for (i = 0; i < COM2.RX_Cnt; i++) {
                        TX1_write2buff(RX2_Buffer[i]);
                    }
                }
                COM2.RX_Cnt = 0;
            }
        }
        os_wait2(K_TMO, 2); // 5ms x 2 = 10ms
    }
}