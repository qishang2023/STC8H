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
#include "util.h"

//DWORD reverse4(DWORD d)
//{   
//    DWORD ret;
//    
//    ((BYTE *)&ret)[0] = ((BYTE *)&d)[3];
//    ((BYTE *)&ret)[1] = ((BYTE *)&d)[2];
//    ((BYTE *)&ret)[2] = ((BYTE *)&d)[1];
//    ((BYTE *)&ret)[3] = ((BYTE *)&d)[0];
//
//    return ret;
//}
   
WORD reverse2(WORD w)
{
    WORD ret;
    
    ((BYTE *)&ret)[0] = ((BYTE *)&w)[1];
    ((BYTE *)&ret)[1] = ((BYTE *)&w)[0];

    return ret;
}
