#include "encoder.h"

/**
 * @brief  把TIM3初始化为编码器接口模式
 * @param  无
 * @retval 无
 */
void Encoder_Init_TIM3(void) {
    TIM_TimeBaseInitTypeDef 	TIM_TimeBaseStructure;
    TIM_ICInitTypeDef 			TIM_ICInitStructure;
    GPIO_InitTypeDef 			GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(Encode_TIMx_CLK_L, ENABLE); //使能定时器3的时钟
    RCC_APB2PeriphClockCmd(Encode_GPIOx_CLK, ENABLE);  //使能PA端口时钟

    GPIO_InitStructure.GPIO_Pin = Encode_PHASE_A_L | Encode_PHASE_B_L; //端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(Encode_PORT, &GPIO_InitStructure);

    TIM_DeInit(Encode_TMIx_L);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数
    TIM_TimeBaseInit(Encode_TMIx_L, &TIM_TimeBaseStructure);
    //使用编码器模式3
    TIM_EncoderInterfaceConfig(Encode_TMIx_L, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(Encode_TMIx_L, &TIM_ICInitStructure);
    TIM_ClearFlag(Encode_TMIx_L, TIM_FLAG_Update); //清除TIM的更新标志位
    TIM_ITConfig(Encode_TMIx_L, TIM_IT_Update, ENABLE);

    TIM_SetCounter(Encode_TMIx_L, 0);

    TIM_Cmd(Encode_TMIx_L, ENABLE);

    Encode_TMIx_L->CNT = 0x7fff;
}

void Encoder_Init_TIM2(void) {
    TIM_TimeBaseInitTypeDef 	TIM_TimeBaseStructure;
    TIM_ICInitTypeDef 			TIM_ICInitStructure;
    GPIO_InitTypeDef 			GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(Encode_TIMx_CLK_R, ENABLE); //使能定时器3的时钟
    RCC_APB2PeriphClockCmd(Encode_GPIOx_CLK, ENABLE);  //使能PA端口时钟

    GPIO_InitStructure.GPIO_Pin = Encode_PHASE_A_R | Encode_PHASE_B_R; //端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //浮空输入
    GPIO_Init(Encode_PORT, &GPIO_InitStructure);                       //根据设定参数初始化GPIOA

    TIM_DeInit(Encode_TMIx_R);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                  // 预分频器
    TIM_TimeBaseStructure.TIM_Period = 65535;                   //设定计数器自动重装值ARR
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //选择时钟分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数
    TIM_TimeBaseInit(Encode_TMIx_R, &TIM_TimeBaseStructure);
    //使用编码器模式3
    TIM_EncoderInterfaceConfig(Encode_TMIx_R, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(Encode_TMIx_R, &TIM_ICInitStructure);
    TIM_ClearFlag(Encode_TMIx_R, TIM_FLAG_Update); //清除TIM的更新标志位
    TIM_ITConfig(Encode_TMIx_R, TIM_IT_Update, ENABLE);

    TIM_SetCounter(Encode_TMIx_R, 0);

    TIM_Cmd(Encode_TMIx_R, ENABLE);

    Encode_TMIx_R->CNT = 0x7fff;
}

/**
 * @brief  读取编码器计数
 * @param  无
 * @retval 一定时间内编码器的计数
 */

int Get_Encoder(u8 TIMx) {
    int Encoder_Value;
    switch (TIMx) {
    case 2:
        Encoder_Value = Encode_TMIx_R->CNT - 0x7fff;
        Encode_TMIx_R->CNT = 0x7fff;
        break;
    case 3:
        Encoder_Value = Encode_TMIx_L->CNT - 0x7fff;
        Encode_TMIx_L->CNT = 0x7fff;
        break;
    default:
        Encoder_Value = 0;
    }
    return Encoder_Value;
}

void TIM3_IRQHandler(void) {
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != 0) {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

void TIM2_IRQHandler(void) {
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != 0) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

