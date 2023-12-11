#include "RTX51TNY.H"
#include "bsp_track.h"
#include "bsp_light.h"
#include "UART.h"
#include "NVIC.h"
#include "Switch.h"
#include "bsp_key.h"
#include "bsp_battery.h"
#include "bsp_ranging.h"

void UART_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    COMx_InitDefine COMx_InitStructure; // �ṹ����

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx; // ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;     // ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;       // ������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;         // ��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;        // �����ʼӱ�, ENABLE��DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);     // ��ʼ������1 UART1,UART2,UART3,UART4
    NVIC_UART1_Init(ENABLE, Priority_1);                // �ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    UART1_SW(UART1_SW_P30_P31);

    // �ṹ����
    GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1; // ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_InitStructure.Mode = GPIO_PullUp;             // ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);        // ��ʼ��
}

void sys_init()
{
    light_init();
    // track_init();
    UART_init();
    key_init();
    ranging_init();
    // battery_init();
}

void start_main() _task_ 0
{
    sys_init();
    os_create_task(1);
    os_create_task(2);
    os_delete_task(0);
}

void light() _task_ 1
{
    float distance;
    while (1) {
        // light_toggle(0);
        // os_wait2(K_TMO,200);
        // light_toggle(1);
        // os_wait2(K_TMO,200);
        if (key_num) {
            key_num = 0;
            distance = ranging_get_distance();
            printf("distance = %.2fCM", distance);
            // printf("%.2f",ranging_get_distance());
            light_toggle(2);
            // os_wait2(K_TMO, 200);
        }
    }
}

void key() _task_ 2
{
    while (1) {
        key_loop();
        // trcak_get_state();
        // printf("%.2f\n",battery_get_voltage());
        os_wait2(K_TMO, 4);
    }
}
