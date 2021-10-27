#ifndef __ENCODER_H
#define __ENCODER_H 			   
#include "sys.h"  
 

#define Encode_GPIOx_CLK    RCC_APB2Periph_GPIOA
#define Encode_PORT         GPIOA

/**************************Left********************************/
#define Encode_TIMx_CLK_L   RCC_APB1Periph_TIM3
#define Encode_TMIx_L       TIM3
#define Encode_PHASE_A_L    GPIO_Pin_6        
#define Encode_PHASE_B_L    GPIO_Pin_7 
/**************************Left********************************/

/**************************Right*******************************/
#define Encode_TIMx_CLK_R   RCC_APB1Periph_TIM2
#define Encode_TMIx_R       TIM2
#define Encode_PHASE_A_R    GPIO_Pin_0      
#define Encode_PHASE_B_R    GPIO_Pin_1
/**************************Right*******************************/

void Encoder_Init_TIM2(void);
void Encoder_Init_TIM3(void);
int Get_Encoder(u8 TIMx);

void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);


#endif





























