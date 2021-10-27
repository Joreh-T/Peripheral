#ifndef __SEND_DATA_H__
#define __SEND_DATA_H__

#include "sys.h"

#define USARTx  USART1 

typedef union {
    float fdata;
    unsigned long ldata;
} FloatLongType;

void Float_to_Byte(float f,u8 *byte);
void VOFA_Send_Data(int *data, u8 *byte);
void VOFA_Send_Tail(void);

#endif

