#ifndef __INFRARED_H__
#define __INFRARED_H__


#include "sys.h"


#define INFRARED_GPIOx_CLK      RCC_APB2Periph_GPIOB
#define INFRARED_PORT           GPIOA
#define INFRARED_PIN_R          GPIO_Pin_14
#define INFRARED_PIN_L          GPIO_Pin_15


void Infrared_Init(void);

#endif

