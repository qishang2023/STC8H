#include "RTX51TNY.H"
#include "STC8H.H"
#include "bsp_Nixie.h"
#include "bsp_MATRIX.h"
#include "bsp_UART.h"
// P5.3 闪烁
void sys_init()
{
    P5M1 &= ~0x08;
    P5M0 &= ~0x08;
    nixie_init();
    MATRIX_init();
    UART_init();
}

// 这里函数名可随意, 建议不要使用start, 会和I2C.h里的Start冲突
void main_start() _task_ 0
{
    sys_init();
    // 创建任务 1
    // printf("start...");
    os_create_task(1);
    os_create_task(2);
    // 结束任务 0
    os_delete_task(0);
}

void task_0() _task_ 1
{
    u8 i, num = 0;
    while (1) {
        if (matrix_num != 0) {
            if (matrix_num <= 4) {
                num++;
            }
            if (matrix_num >= 12) {
                num--;
            }
            matrix_num = 0;
        }
        for (i = 1; i <= 8; i++) {
            nixie_display(num, i);
        }
    }

    // os_wait1(K_SIG);
    // os_delete_task(0);
}

void task_1() _task_ 2
{
    while (1) {
        matrix_loop();
        // if(matrix_num != 0){
        // 	os_send_signal(1);
        // }
        os_wait2(K_IVL, 4);
    }
}