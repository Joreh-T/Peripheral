#include "Infrared.h"

/**
 * @brief  红外传感器初始化
 * @param  无
 * @retval 无
 */
void Infrared_Init(void) {

    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(INFRARED_GPIOx_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin = INFRARED_PIN_R | INFRARED_PIN_L;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
    GPIO_Init(INFRARED_PORT, &GPIO_InitStructure);
}
