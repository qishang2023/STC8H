#include "usb.h"
#include "bsp_MATRIX.h"
#include "bsp_Timer.h"
#include "GPIO.h"

extern void usb_class_in(BYTE key[]);

u8 key_map[4][4] = {
    {0x14, 0x1A, 0x08, 0x15},
    {0x04, 0x16, 0x07, 0x09},
    {0x00, 0x06, 0x19, 0x2A},
    {0x00, 0x00, 0x00, 0x2C},
};

void scan_and_send()
{
    u8 keys[8] = {0};
    u8 row, col, pos = 2;
    u16 last_states = matrix_state, key_states;
    matrix_GetState();
    key_states = matrix_state;

    if (key_states == last_states) {
        return;
    }

    // 数据发生变化, 才发送

    // 先判定ModifierKeys  // index: 0
    if (key_states & (1 << 12)) keys[0] |= 0x01; // LCtrl
    if (key_states & (1 << 8)) keys[0] |= 0x02;  // LShift
    if (key_states & (1 << 14)) keys[0] |= 0x04; // LAlt
    if (key_states & (1 << 13)) keys[0] |= 0x08; // LGui

    // 循环扫描其他按键 // index: 2-7
    for (row = 0; row < 4; row++) { // 每行

        for (col = 0; col < 4; col++) { // 1行每列
            u8 usage_id = key_map[row][col];

            if (usage_id == 0x00) continue; // 遇到Modifier跳过

            // 当前按钮是否按下, 按下了, 加入到keys
            if (key_states & (1 << (4 * row + col))) {
                keys[pos++] = usage_id;
                // pos>7 结束列循环
                if (pos > 7) break;
            }
        }
        // 结束行循环
        if (pos > 7) break;
    }

    usb_class_in(keys);
}

void usb_keyboard_on_recv(u8 led)
{
    P20 = !(led & 0x01);
    P21 = !(led & 0x02);
    P22 = !(led & 0x04);
}

void main()
{
    P2_MODE_OUT_PP(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
    P4_MODE_OUT_PP(GPIO_Pin_5);
    Timer_init();
    MATRIX_init();
    usb_init();
    EA  = 1;
    P45 = 0;

    while (1) {
        if (scan_key == 1) {
            scan_and_send();
            scan_key = 0;
        }
    }
}