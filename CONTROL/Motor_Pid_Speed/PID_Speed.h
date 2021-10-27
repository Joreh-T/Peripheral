#ifndef __PID_Speed_H__
#define __PID_Speed_H__

#include "sys.h"

struct PID_param{
    float Kp, Ki, Kd;   // 比例、积分、微分系数
    int target;         // 目标值
    int err_0;          // 当前误差
    int err_1;          // 上次的误差
    int err_2;          // 上上次的误差
    int speed_now;      // 当前速度
    int dertal;         // 增量
    int output_val;     // 输出值
};

#define PID_TIMx_CLK    RCC_APB1Periph_TIM6
#define PID_TIMx        TIM6
void PID_TIM6_Init(u16 arr, u16 psc);
void TIM6_IRQHandler(void);
void PID_Init(void);


float PID_left_realize(float actual_val_left);
float PID_right_realize(float actual_val_right);
void AutoReloadCallback(void);

#endif

