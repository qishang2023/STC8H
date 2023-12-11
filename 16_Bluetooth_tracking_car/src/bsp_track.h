#ifndef __BSP_TRACK_H
#define __BSP_TRACK_H

#include "GPIO.h"

#define TRACK_L    P33
#define TRACK_ML   P32
#define TRACK_M    P50
#define TRACK_MR   P06
#define TRACK_R    P47

extern u8 track_state;

void track_init();
void trcak_get_state();

#endif // !__BSP_TRACK_H
