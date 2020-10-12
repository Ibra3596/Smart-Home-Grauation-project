/*
 * MC_1.c
 *
 * Created: 10/8/2020 12:41:18 AM
 * Author : Ibrahim
 */ 

#include "SPI.h"
#include "UART.h"
#define F_CPU 8000000
#include <util/delay.h>

extern uint8 volatile Rx_data;

//extern uint8 volatile SPI_TXData;
extern uint8 volatile SPI_RXData;

int main(void)
{
	uint8 UART_data = Rx_data ;
	uint8 Received_Data = 0 ;
	
	UART_Init();
	
	LCD_Init();
	
	
	//uint8 Trans_Data = 2;
	DIO_SetPinDir(DIO_PORTD ,DIO_PIN5 , DIO_PIN_OUTPUT);
	
	SPI_MasterInit();
	SPI_InitTrans();
	_delay_ms(1000);
	
	while (1)
	{
		//UART_data = UART_ReceiveByte();
		if (Rx_data)
		{
			//UART_data = Rx_data;
			
			LCD_GoTo(0,0);
			LCD_WriteData(Rx_data);
			
			//Received_Data = 
			SPI_transive(Rx_data);	
			
			//Rx_data = 0;
		}
		
		
		if (SPI_RXData == 1)
		{
			LCD_GoTo(1,0);
			LCD_WriteData(UART_data);
			LCD_WriteString(" delivered");
			
			DIO_TogglePin(DIO_PORTD , DIO_PIN5);
			
			Received_Data = 0 ;
		}
		
		_delay_ms(1000);
	}
}


