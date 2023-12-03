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
    u8 inputs[4] = {0};
    u8 row, col, pos = 2;
    u16 last_states = matrix_state, key_states;
    matrix_GetState();
    key_states = matrix_state;

    if (key_states == last_states) {
        return;
    }

    // 数据发生变化, 才发送

    // 先判定ModifierKeys  // index: 0
    if (key_states & (1 << 9)) inputs[0] |= 0x01;  // LCtrl
    if (key_states & (1 << 11)) inputs[0] |= 0x02; // LShift
    if (key_states & (1 << 6)) inputs[0] |= 0x04;  // LAlt

    if (key_states & (1 << 13)) inputs[1] = -10;
    else if (key_states & (1 << 15)) inputs[1] = 10;

    if (key_states & (1 << 10)) inputs[2] = -10;
    else if (key_states & (1 << 14)) inputs[2] = 10;

    if (key_states & (1 << 3)) inputs[3] = -10;
    else if (key_states & (1 << 7)) inputs[3] = 10;
    usb_class_in(inputs);
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