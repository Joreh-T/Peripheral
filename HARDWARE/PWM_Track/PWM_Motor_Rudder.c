#include "PWM_Motor_Rudder.h"

/**
 * @brief  电机PWM初始化
 * @param  arr--自动重装载值   psc--预分频系数
 * @retval 无
 */
void Motor_PWM_TIM5_Init(u16 arr, u16 psc) {
    GPIO_InitTypeDef 			GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef 	TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef 			TIM_OCInitStructure;

    // 开启IO口&定时器时钟
    RCC_APB2PeriphClockCmd(MOTOR_PWM_GPIOx_CLK | MOTOR_INx_GPIOx_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(MOTOR_PWM_TIMx_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽
    GPIO_InitStructure.GPIO_Pin = MOTOR_PWM_PIN_R | MOTOR_PWM_PIN_L;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MOTOR_PWM_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = MOTOR_IN1_PIN | MOTOR_IN2_PIN | MOTOR_IN3_PIN | MOTOR_IN4_PIN;
    GPIO_Init(MOTOR_INx_PORT, &GPIO_InitStructure);

    TIM_DeInit(MOTOR_PWM_TIMx);
    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);             // 初始化定时器
    TIM_TimeBaseInitStructure.TIM_Period = arr;                     // 自动重装载值
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                  // 预分频系数
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 分频因子
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseInit(MOTOR_PWM_TIMx, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               // PWM模式1
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; // 设置待装入捕获比较寄存器的脉冲值
    TIM_OC3Init(MOTOR_PWM_TIMx, &TIM_OCInitStructure);          // 通道3
    TIM_OC4Init(MOTOR_PWM_TIMx, &TIM_OCInitStructure);          // 通道4
    TIM_OC3PreloadConfig(MOTOR_PWM_TIMx, TIM_OCPreload_Enable); // 使能预装载寄存器
    TIM_OC4PreloadConfig(MOTOR_PWM_TIMx, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(MOTOR_PWM_TIMx, ENABLE); // 使能TIMx在ARR上的预装载寄存器
    TIM_Cmd(MOTOR_PWM_TIMx, ENABLE);              // 使能TIMx
}

/**
 * @brief  舵机PWM初始化
 * @param  arr--自动重装载值   psc--预分频系数
 * @retval 无
引脚：PD12
 */
void RUDDER_PWM_TIM4_Init(u16 arr, u16 psc) {
    GPIO_InitTypeDef 			GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef 	TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef 			TIM_OCInitStructure;

    // 开启IO口&定时器时钟
    RCC_APB2PeriphClockCmd(RUDDER_PWM_GPIOx_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(RUDDER_PWM_TIMx_CLK, ENABLE);
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//开启复用
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽
    GPIO_InitStructure.GPIO_Pin = RUDDER_PWM_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RUDDER_PWM_PORT, &GPIO_InitStructure);

    TIM_DeInit(RUDDER_PWM_TIMx);
    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(RUDDER_PWM_TIMx, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; // 设置待装入捕获比较寄存器的脉冲值
    TIM_OC1Init(RUDDER_PWM_TIMx, &TIM_OCInitStructure);          // 通道1
    TIM_OC1PreloadConfig(RUDDER_PWM_TIMx, TIM_OCPreload_Enable); // 使能预装载寄存器


    TIM_ARRPreloadConfig(RUDDER_PWM_TIMx, ENABLE); // 使能TIMx在ARR上的预装载寄存器
    TIM_Cmd(RUDDER_PWM_TIMx, ENABLE);              // 使能TIMx
}
