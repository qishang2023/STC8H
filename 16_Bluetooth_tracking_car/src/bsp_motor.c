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
    pwmInit.PWM_Mode      = CCMRn_PWM_MODE1;                           // ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    pwmInit.PWM_Duty      = PERIOD * LH_duty / 100;    // PWMռ�ձ�ʱ��, 0~Period
    pwmInit.PWM_EnoSelect = (cfg.LH_speed == 0 ? 0 : (ENO1P | ENO1N)); // ���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM1, &pwmInit);                                 // ��ʼ��PWM
    // ����PWM2 - RH �Һ�
    pwmInit.PWM_Mode      = CCMRn_PWM_MODE2;                           // ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    pwmInit.PWM_Duty      = PERIOD * RH_duty / 100;    // PWMռ�ձ�ʱ��, 0~Period
    pwmInit.PWM_EnoSelect = (cfg.RH_speed == 0 ? 0 : (ENO2P | ENO2N)); // ���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM2, &pwmInit);                                 // ��ʼ��PWM
    // ����PWM3 - RQ ��ǰ
    pwmInit.PWM_Mode      = CCMRn_PWM_MODE1;                           // ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    pwmInit.PWM_Duty      = PERIOD * RQ_duty / 100;    // PWMռ�ձ�ʱ��, 0~Period
    pwmInit.PWM_EnoSelect = (cfg.RQ_speed == 0 ? 0 : (ENO3P | ENO3N)); // ���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM3, &pwmInit);
    // ����PWM4 - LQ ��ǰ
    pwmInit.PWM_Mode      = CCMRn_PWM_MODE2;                           // ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    pwmInit.PWM_Duty      = PERIOD * LQ_duty / 100;    // PWMռ�ձ�ʱ��, 0~Period
    pwmInit.PWM_EnoSelect = (cfg.LQ_speed == 0 ? 0 : (ENO4P | ENO4N)); // ���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM4, &pwmInit);

    // ����PWMA
    pwmInit.PWM_Period        = PERIOD - 1; // ����ʱ��,   0~65535
    pwmInit.PWM_DeadTime      = 0;          // ��������������, 0~255
    pwmInit.PWM_MainOutEnable = ENABLE;     // �����ʹ��, ENABLE,DISABLE
    pwmInit.PWM_CEN_Enable    = ENABLE;     // ʹ�ܼ�����, ENABLE,DISABLE
    PWM_Configuration(PWMA, &pwmInit);      // ��ʼ��PWMͨ�üĴ���,  PWMA,PWMB

    // �л�PWMͨ��
    // LH ���
    PWM1_SW(PWM1_SW_P20_P21); // PWM1_SW_P10_P11,PWM1_SW_P20_P21,PWM1_SW_P60_P61
    // RH �Һ�
    PWM2_SW(PWM2_SW_P22_P23); // PWM2_SW_P12_P13,PWM2_SW_P22_P23,PWM2_SW_P62_P63
    // RQ ��ǰ
    PWM3_SW(PWM3_SW_P14_P15); // PWM3_SW_P14_P15,PWM3_SW_P24_P25,PWM3_SW_P64_P65
    // LQ ��ǰ
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