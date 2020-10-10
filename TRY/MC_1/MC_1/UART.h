/*
 * UART.h
 *
 * Created: 9/5/2020 10:21:03 PM
 *  Author: Ibrahim
 */ 


#ifndef UART_H_
#define UART_H_

#include "DIO.h"


void UART_Init(void);

void UART_SendByte(uint8 byte);

void UART_SendString(uint8* );

uint8 UART_ReceiveByte(void);

uint8* UART_ReceiveString(void);



#endif /* UART_H_ */