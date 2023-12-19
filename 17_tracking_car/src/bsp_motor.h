#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H

#include "GPIO.h"
#include "STC8H_PWM.h"
#include "switch.h"

#define LQ_B  P17
#define LQ_F  P16

#define RQ_B  P15
#define RQ_F  P14

#define LH_B  P20
#define LH_F  P21

#define RH_B  P23
#define RH_F  P22

#define PERIOD (MAIN_Fosc / 1000)

typedef struct {
    int LQ_speed;
    int LH_speed;
    int RQ_speed;
    int RH_speed;
} MotorCfg;

void motor_init();
void Motors_forward(int speed);
void Motors_back(int speed);
void Motor_left_mini(int speed);
void Motor_right_mini(int speed);
void Motor_left(int speed);
void Motor_right(int speed);
void Motors_around(int speed);
void Motors_stop();

#endif // !__BSP_MOTOR_H
