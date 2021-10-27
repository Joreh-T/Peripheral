#include "PID_Speed.h"

// #define PengYuyan // 位置式
#define SunWukong    // 增量式

#if defined PengYuyan

struct PID_Init {
    float target_val; //目标值
    float err;        //偏差值
    float err_last;   //上一个偏差值
    float Kp, Ki, Kd; //比例、积分、微分系数
    float integral;   //积分值
    float output_val; //输出值
};

struct PID_Init PID_Speed_Left;
struct PID_Init PID_Speed_Right;

float PID_left_realize(float actual_val_left) //左电机PID实现
{
    /*计算目标值与实际值的误差*/
    PID_Speed_Left.err = PID_Speed_Left.target_val - actual_val_left;

    /*积分项*/
    PID_Speed_Left.integral += PID_Speed_Left.err;

    /*PID算法实现*/
    PID_Speed_Left.output_val = PID_Speed_Left.Kp * PID_Speed_Left.err + PID_Speed_Left.Ki * PID_Speed_Left.integral + PID_Speed_Left.Kd * (PID_Speed_Left.err - PID_Speed_Left.err_last);

    /*误差传递*/
    PID_Speed_Left.err_last = PID_Speed_Left.err;

    /*返回当前实际值*/
    return PID_Speed_Left.output_val;
}

float PID_right_realize(float actual_val_right) {
    /*计算目标值与实际值的误差*/
    PID_Speed_Right.err = PID_Speed_Right.target_val - actual_val_right;

    /*积分项*/
    PID_Speed_Right.integral += PID_Speed_Right.err;

    /*PID算法实现*/
    PID_Speed_Right.output_val = PID_Speed_Right.Kp * PID_Speed_Right.err + PID_Speed_Right.Ki * PID_Speed_Right.integral + PID_Speed_Right.Kd * (PID_Speed_Right.err - PID_Speed_Right.err_last);

    /*误差传递*/
    PID_Speed_Right.err_last = PID_Speed_Right.err;

    /*返回当前实际值*/
    return PID_Speed_Right.output_val;
}

//周期定时器回调函数

void AutoReloadCallback(void) {
    int sum_left = 0;     /*编码器值（PID输入）*/
    int res_pwm_left = 0; /*PWM值（PID输出）*/
    int sum_right = 0;
    int res_pwm_right = 0;

    sum_left = Get_Encoder(3); /*读取编码器测量的速度值*/
    sum_right = Get_Encoder(2);
    res_pwm_left = PID_left_realize(sum_left);    /*进行PID运算，得到PWM输出值*/
    res_pwm_right = PID_right_realize(sum_right); /*根据PWM值控制电机转动*/

    TIM_SetCompare4(TIM5, res_pwm_left);  /*根据PWM值控制电机转动*/
    TIM_SetCompare3(TIM5, res_pwm_right); /*根据PWM值控制电机转动*/
}

#elif defined SunWukong

void PID_TIM6_Init(u16 arr, u16 psc) {
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
    NVIC_InitTypeDef            NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(PID_TIMx_CLK, ENABLE);

    TIM_DeInit(PID_TIMx);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    
    // TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      // 基本定时器没有 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     // TIM向上计数模式
    TIM_TimeBaseInit(PID_TIMx, &TIM_TimeBaseStructure);
    TIM_ITConfig(PID_TIMx, TIM_IT_Update, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;                 // TIM6中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       // 先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              // 从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 // IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(PID_TIMx, ENABLE);
}

extern struct PID_param pid;
extern int Speed_R, Speed_L;
void PID_Init(void) {
    pid.Kp = 20;
    pid.Ki = 0.001;
    pid.Kd = 0.001;
    pid.speed_now = 0;
    pid.target =10;
}


void PID_Realize(void) {
    Speed_R = Get_Encoder(2); Speed_L = Get_Encoder(3);
    pid.speed_now = (Speed_L + Speed_R)*0.5;
    pid.err_0 = pid.target - pid.speed_now;
    pid.dertal = pid.Kp*(pid.err_0-pid.err_1)+pid.Ki*pid.err_0+pid.Kd*(pid.err_0+pid.err_2-2*pid.err_1);
    pid.output_val += pid.dertal;
    if(pid.output_val > 1999) pid.output_val = 1999;
    else if(pid.output_val < 0) pid.output_val = 0;
    pid.err_2 = pid.err_1;
    pid.err_1 = pid.err_0;
}

void TIM6_IRQHandler(void) {

    // 检查指定的TIM中断发生与否:TIM 中断源 
    if(TIM_GetITStatus(PID_TIMx, TIM_IT_Update) != RESET) {
        PID_Realize();
        TIM_SetCompare3(TIM5, pid.output_val);
        TIM_SetCompare4(TIM5, pid.output_val);
        // LCD_Clear(BLACK);
        // SWK_LCD_DrawNum(60, 5, GREEN, BLACK, pid.dertal);
        // LCD_DrawFont_GBK16(2, 100, GREEN, BLACK, "pid")
        PAout(8) = ~PAout(8);
        TIM_ClearITPendingBit(PID_TIMx, TIM_IT_Update);
    }
}


#endif
