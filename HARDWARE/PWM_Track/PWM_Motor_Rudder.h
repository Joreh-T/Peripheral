#ifndef __PWM_MOTOR_RUDDER_H__
#define __PWM_MOTOR_RUDDER_H__

#include "sys.h"

//======================================MOTOR=========================================//
#define MOTOR_PWM_GPIOx_CLK         RCC_APB2Periph_GPIOA
#define MOTOR_PWM_TIMx_CLK          RCC_APB1Periph_TIM5
#define MOTOR_PWM_TIMx              TIM5
#define MOTOR_PWM_PORT              GPIOA
#define MOTOR_PWM_PIN_R             GPIO_Pin_2
#define MOTOR_PWM_PIN_L             GPIO_Pin_3

// 电机转向
#define MOTOR_INx_GPIOx_CLK         RCC_APB2Periph_GPIOB
#define MOTOR_INx_PORT              GPIOB
#define MOTOR_IN1_PIN               GPIO_Pin_0
#define MOTOR_IN2_PIN               GPIO_Pin_1
#define MOTOR_IN3_PIN               GPIO_Pin_12
#define MOTOR_IN4_PIN               GPIO_Pin_13

#define IN1_High                    GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define IN2_High                    GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define IN3_High                    GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define IN4_High                    GPIO_SetBits(GPIOB, GPIO_Pin_13)

#define IN1_Low                     GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define IN2_Low                     GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define IN3_Low                     GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define IN4_Low                     GPIO_ResetBits(GPIOB, GPIO_Pin_13)

void Motor_PWM_TIM5_Init(u16 arr, u16 psc);

//======================================MOTOR=========================================//



//======================================RUDDER========================================//
#define RUDDER_PWM_GPIOx_CLK        RCC_APB2Periph_GPIOD
#define RUDDER_PWM_TIMx_CLK         RCC_APB1Periph_TIM4
#define RUDDER_PWM_TIMx             TIM4
#define RUDDER_PWM_PORT             GPIOD
#define RUDDER_PWM_PIN              GPIO_Pin_12

void RUDDER_PWM_TIM4_Init(u16 arr, u16 psc);

//======================================RUDDER========================================//
#endif

