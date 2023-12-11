#include "bsp_motor.h"

PWMx_InitDefine pwmInit;

void motor_init()
{
    P1_MODE_OUT_PP(GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_4);
    P1_MODE_OUT_PP(GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_4);
}

void motor_config(MotorCfg cfg)
{
    int LQ_duty           = cfg.LH_speed * 2 + 50;
    int LH_duty           = cfg.LQ_speed * 2 + 50;
    int RQ_duty           = cfg.RQ_speed * 2 + 50;
    int RH_duty           = cfg.RH_speed * 2 + 50;
    pwmInit.PWM_Mode      = CCMRn_PWM_MODE1;                           // 模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    pwmInit.PWM_Duty      = PERIOD * LH_duty / 100;    // PWM占空比时间, 0~Period
    pwmInit.PWM_EnoSelect = (cfg.LH_speed == 0 ? 0 : (ENO1P | ENO1N)); // 输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM1, &pwmInit);                                 // 初始化PWM
    // 配置PWM2 - RH 右后
    pwmInit.PWM_Mode      = CCMRn_PWM_MODE2;                           // 模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    pwmInit.PWM_Duty      = PERIOD * RH_duty / 100;    // PWM占空比时间, 0~Period
    pwmInit.PWM_EnoSelect = (cfg.RH_speed == 0 ? 0 : (ENO2P | ENO2N)); // 输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM2, &pwmInit);                                 // 初始化PWM
    // 配置PWM3 - RQ 右前
    pwmInit.PWM_Mode      = CCMRn_PWM_MODE1;                           // 模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    pwmInit.PWM_Duty      = PERIOD * RQ_duty / 100;    // PWM占空比时间, 0~Period
    pwmInit.PWM_EnoSelect = (cfg.RQ_speed == 0 ? 0 : (ENO3P | ENO3N)); // 输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM3, &pwmInit);
    // 配置PWM4 - LQ 左前
    pwmInit.PWM_Mode      = CCMRn_PWM_MODE2;                           // 模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    pwmInit.PWM_Duty      = PERIOD * LQ_duty / 100;    // PWM占空比时间, 0~Period
    pwmInit.PWM_EnoSelect = (cfg.LQ_speed == 0 ? 0 : (ENO4P | ENO4N)); // 输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM4, &pwmInit);

    // 配置PWMA
    pwmInit.PWM_Period        = PERIOD - 1; // 周期时间,   0~65535
    pwmInit.PWM_DeadTime      = 0;          // 死区发生器设置, 0~255
    pwmInit.PWM_MainOutEnable = ENABLE;     // 主输出使能, ENABLE,DISABLE
    pwmInit.PWM_CEN_Enable    = ENABLE;     // 使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMA, &pwmInit);      // 初始化PWM通用寄存器,  PWMA,PWMB

    // 切换PWM通道
    // LH 左后
    PWM1_SW(PWM1_SW_P20_P21); // PWM1_SW_P10_P11,PWM1_SW_P20_P21,PWM1_SW_P60_P61
    // RH 右后
    PWM2_SW(PWM2_SW_P22_P23); // PWM2_SW_P12_P13,PWM2_SW_P22_P23,PWM2_SW_P62_P63
    // RQ 右前
    PWM3_SW(PWM3_SW_P14_P15); // PWM3_SW_P14_P15,PWM3_SW_P24_P25,PWM3_SW_P64_P65
    // LQ 左前
    PWM4_SW(PWM4_SW_P16_P17);
}

void Motors_around(int speed)
{
    MotorCfg cfg;
    cfg.LQ_speed = speed;
    cfg.LH_speed = speed;
    cfg.RQ_speed = -speed;
    cfg.RH_speed = -speed;
    motor_config(cfg);
}

void Motors_stop()
{
    MotorCfg cfg;
    cfg.LQ_speed = 0;
    cfg.LH_speed = 0;
    cfg.RQ_speed = 0;
    cfg.RH_speed = 0;
    motor_config(cfg);
}