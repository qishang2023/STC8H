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

void UART_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    COMx_InitDefine COMx_InitStructure; // 结构定义

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx; // 模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;     // 选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;       // 波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;         // 接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;        // 波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);     // 初始化串口1 UART1,UART2,UART3,UART4
    NVIC_UART1_Init(ENABLE, Priority_1);                // 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    UART1_SW(UART1_SW_P30_P31);

    // 结构定义
    GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1; // 指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_InitStructure.Mode = GPIO_PullUp;             // 指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);        // 初始化
}

void sys_init()
{
    EAXSFR();
    light_init();
    // track_init();
    UART_init();
    key_init();
    ranging_init();
    motor_init();
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
    u8 mode = 4;
    while (1) {
        // light_toggle(0);
        // os_wait2(K_TMO,200);
        // light_toggle(1);
        // os_wait2(K_TMO,200);
        if (key_num) {
            key_num = 0;
            // distance = ranging_get_distance();
            // printf("distance = %.2fCM", distance);
            // printf("%.2f",ranging_get_distance());
       		switch(mode){
			// case 0:
			// 	printf("前进\n");
			// 	Motors_forward(70);
			// 	break;
			// case 1:
			// 	printf("后退\n");
			// 	Motors_backward(30);
			// 	break;
			// case 2:
			// 	printf("左转\n");
			// 	Motors_left(60);
			// 	break;
			// case 3:
			// 	printf("右转\n");
			// 	Motors_right(60);
			// 	break;
			case 4:
				// printf("原地掉头\n");
				Motors_around(10);
				break;
			default:
				// printf("停止\n");
				Motors_stop();
				break;
		}
		mode++;
		if(mode > 5){
			mode = 4;
		}
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