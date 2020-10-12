/*
 * MC_2.c
 *
 * Created: 10/8/2020 1:03:25 AM
 * Author : Ibrahim
 */ 

#include "SPI.h"
#include "DC_Motor.h"
#include "Temprature_Sensor.h"

#define F_CPU 8000000
#include <util/delay.h>

extern uint8 volatile SPI_RXData;

int main(void)
{
	
	uint8 Received_Data = 0 ;
	uint8 Trans_Data = 1;
	
	DIO_SetPinDir(DIO_PORTD ,DIO_PIN5 , DIO_PIN_OUTPUT);
	
	LCD_Init();
	
	uint16 temp = 0;
	Tempsensor_Init();
	DC_Motor_Init();

	
	SPI_SlaveInit();
	
	
	while (1)
	{
		Tempsensor_Read(&temp);
		Control_fan( &temp);
		
		//Received_Data = SPI_transive(Trans_Data);
		//SPI_RXData =SPI_transive(Trans_Data);
		 SPI_transive(Trans_Data);
		
		if (SPI_RXData)
		{
			LCD_WriteData(SPI_RXData);
			if (SPI_RXData == 'A')
			{
				DIO_SetPinValue(DIO_PORTD , DIO_PIN5 , DIO_PIN_HIGH);
			}
			else if (SPI_RXData == 'a')
			{
				DIO_SetPinValue(DIO_PORTD , DIO_PIN5 , DIO_PIN_LOW);
			}
			
			else if (SPI_RXData == 'B')
			{
				DC_Motor_SetDirection(CLOCKWISE);
				DC_Motor_Start();
			}
			
			else if (SPI_RXData == 'b')
			{
				DC_Motor_Stop();
			}
			
			/*
			else if (SPI_RXData == 'C')
			{

			}
			
			else if (SPI_RXData == 'c')
			{

			}
			*/
			
			Received_Data = 0;
			
		}
		
		_delay_ms(1000);
	}
}


void Control_fan(uint16* temp)
{
	
	
		//Tempsensor_Read(&temp);
		
		if (temp > 10 && temp <=20)
		{
			
			DC_Motor_SetSpeed(3);
			//DC_Motor_Start();
			
		}
		else if (temp > 20 && temp <=25)
		{
			DC_Motor_SetSpeed(5);
			//DC_Motor_Start();
		}
		else if (temp > 25 && temp <=30)
		{
			DC_Motor_SetSpeed(8);
			//DC_Motor_Start();
		}
		else if (temp > 30)
		{
			DC_Motor_SetSpeed(10);
			//DC_Motor_Start();
		}
		else
		{
			DC_Motor_Stop();
		}
	
}
