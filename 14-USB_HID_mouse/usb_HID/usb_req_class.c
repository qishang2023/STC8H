/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序        */
/*---------------------------------------------------------------------*/

#include "usb.h"
#include "usb_req_class.h"

BYTE bHidIdle;

void usb_req_class()
{
    switch (Setup.bRequest) {
        case GET_REPORT:
            usb_get_report();
            break;
        case SET_REPORT:
            usb_set_report();
            break;
        case GET_IDLE:
            usb_get_idle();
            break;
        case SET_IDLE:
            usb_set_idle();
            break;
        case GET_PROTOCOL:
            usb_get_protocol();
            break;
        case SET_PROTOCOL:
            usb_set_protocol();
            break;
        default:
            usb_setup_stall();
            return;
    }
}

void usb_get_report()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (IN_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT))) {
        usb_setup_stall();
        return;
    }

    Ep0State.pData = UsbBuffer;
    Ep0State.wSize = Setup.wLength;

    usb_setup_in();
}

void usb_set_report()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (OUT_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT))) {
        usb_setup_stall();
        return;
    }

    Ep0State.pData = UsbBuffer;
    Ep0State.wSize = Setup.wLength;

    usb_setup_out();
}

void usb_get_idle()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (IN_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT))) {
        usb_setup_stall();
        return;
    }

    Ep0State.pData = &bHidIdle;
    Ep0State.wSize = 1;

    usb_setup_in();
}

void usb_set_idle()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (OUT_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT))) {
        usb_setup_stall();
        return;
    }

    bHidIdle = Setup.wValueH;

    usb_setup_status();
}

void usb_get_protocol()
{
    usb_setup_stall();
}

void usb_set_protocol()
{
    usb_setup_stall();
}

/* void usb_class_out()
{
    BYTE led;

    if (usb_bulk_intr_out(UsbBuffer, 1) == 1)
    {
        P4M0 &= ~0x01;
        P4M1 &= ~0x01;
        P6M0 &= ~0xe0;
        P6M1 &= ~0xe0;
        P40 = 0;

        led = UsbBuffer[0];
        LED_NUM = !(led & 0x01);
        LED_CAPS = !(led & 0x02);
        LED_SCROLL = !(led & 0x04);
    }
} */


void usb_class_in(BYTE key[])
{
    BYTE i;
    if (DeviceState != DEVSTATE_CONFIGURED)
        return;

    if (!UsbInBusy) {
        IE2 &= ~0x80; // EUSB = 0;
        UsbInBusy = 1;
        usb_write_reg(INDEX, 1);
        for (i = 0; i < 4; i++) {
            usb_write_reg(FIFO1, key[i]);
        }
        usb_write_reg(INCSR1, INIPRDY);
        IE2 |= 0x80; // EUSB = 1;
    }
}

void usb_class_out(){
    BYTE led;
    
    if (usb_bulk_intr_out(UsbBuffer, 1) == 1)
    {
        led = UsbBuffer[0];
				// 1 1 1 1 - 0 1 0 1
			
		usb_keyboard_on_recv(led);
    }
	
}