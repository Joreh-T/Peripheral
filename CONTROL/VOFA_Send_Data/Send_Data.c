//============================================================================//
// Author      : 孙雾崆
// Date        : 2021-10-26 21:26
// Editor      : VScode Tab size(4)
// Description : Send data to vofa+ , Protocol:justfloat
// VOFA+       :https://www.vofa.plus/
//============================================================================//
#include "Send_Data.h"

int length;
const u8 tail[4] = {0X00, 0X00, 0X80, 0X7f};


/**
 * @brief  将浮点数f转化为4个字节数据存放在byte[4]中
 * @param  f--待转换浮点数  byte--存放浮点数的数组
 * @retval 无
 */
void Float_to_Byte(float f,u8 *byte) {
	FloatLongType fl;
	fl.fdata=f;
	byte[0]=(unsigned char)fl.ldata;
	byte[1]=(unsigned char)(fl.ldata>>8);
	byte[2]=(unsigned char)(fl.ldata>>16);
	byte[3]=(unsigned char)(fl.ldata>>24);
}

/**
 * @brief  向vofa+发送数据，可以连续调用这个函数发送不同的几组数据
 *         一组数据一个曲线，第一组发送的数据，编号0，以此类推，0、1、2
 * @param  data--待转发送数据  byte--存放浮点数的数组
 * @retval 无
 */
void VOFA_Send_Data(int *data, u8 *byte) {
    Float_to_Byte(*data, byte);
    for (length = 0; length < 4; length++) {
        USART_SendData(USARTx, byte[length]);                       //向串口1发送数据
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) != SET);  //等待发送结束
    }
}

/**
 * @brief  vofa+尾帧，发送完n组数据后必须调用这个函数，发送尾帧
 * @param  无
 * @retval 无
 */
void VOFA_Send_Tail(void) {
    for (length = 0; length < 4; length++) {
        USART_SendData(USARTx, tail[length]); //向串口1发送数据
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) != SET); //等待发送结束
    }
}

