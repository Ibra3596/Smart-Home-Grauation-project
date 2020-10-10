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

int main(void)
{
	uint8 UART_data = 0 ;
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
		UART_data = UART_ReceiveByte();
		
		Received_Data = SPI_transive(UART_data);
		
		if (Received_Data == 1)
		{
			LCD_GoTo(1,0);
			LCD_WriteData(UART_data);
			LCD_WriteString(" delivered");
			
			DIO_TogglePin(DIO_PORTD , DIO_PIN5);
			
			Received_Data = 0 ;
		}
		
		if (UART_data)
		{
			LCD_GoTo(0,0);
			LCD_WriteData(UART_data);
			
			UART_data = 0;
		}
		
		
		_delay_ms(1000);
	}
}


