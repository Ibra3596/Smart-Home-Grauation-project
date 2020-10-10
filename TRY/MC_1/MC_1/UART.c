	/*
 * UART.c
 *
 * Created: 9/5/2020 10:21:23 PM
 *  Author: Ibrahim
 */ 


#include "UART.h"
#define NULL ((void*)(0))

void UART_Init(void)
{
	uint32 BR_Value = 0; // value lTER TO BE ASSIGNED TO UBRR
	
	DIO_SetPinDir(DIO_PORTD , DIO_PIN0 , DIO_PIN_INPUT); //RX Pin set to input
	DIO_SetPinDir(DIO_PORTD , DIO_PIN1 , DIO_PIN_OUTPUT); // TX Pin set to output
	
	//Enable to read & transmission operation 
	
	UCSRB |= 0x18 ; // 00011000 bit 3 enable transmit , bit 4 enable read
	
	//selecting character size to 8 bits	
	
	UCSRC |= 0x86; //bit7 to select write to UCSRC reg , 11 to bits 2,1 to select 8-bit mode
	
	//desired baud rate is 9600
	
	BR_Value = ((80000) / (16 * (96))) -1 ; //same as ((8000000)/16*(9600))-1 but with reduced form to avoid overflow
	
	UBRRL = BR_Value;
}

void UART_SendByte(uint8 data)
{
	// writing data to UDR register
	UDR = data ;
	
	while (GET_BIT(UCSRA , 5) == 0); //wait till data register empty flag is set
	
	/*won't exit the function until the tx buffer is empty
	 and ready to be assigned to new data to be sent */ 
	
}

void UART_SendString(uint8* str)
{
	uint8 i =0;
	while(str[i] != '\0')
	{
		UART_SendByte(str[i]);
		
		i++;
	}
	
}

uint8 UART_ReceiveByte(void)
{
	uint8 data = 0;
	
	while (GET_BIT(UCSRA , 7) ==0);
	data = UDR;
	
	return data;
}
