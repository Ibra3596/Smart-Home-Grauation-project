/*
 * MC_2.c
 *
 * Created: 10/8/2020 1:03:25 AM
 * Author : Ibrahim
 */ 

#include "SPI.h"
#include "DC_Motor.h"
#include "Temprature_Sensor.h"
#include "Servo.h"

#define F_CPU 8000000
#include <util/delay.h>

extern uint16 ADC_value;

int main(void)
{
	
	uint8 Received_Data = 0 ;
	uint8 Trans_Data = 1;
	
	DIO_SetPinDir(DIO_PORTD ,DIO_PIN6 , DIO_PIN_OUTPUT);
	
	LCD_Init();
	
	uint16 temp = 0;
	Tempsensor_Init();
	DC_Motor_Init();
	Servo_Init();
	
	SPI_SlaveInit();
	
	
	while (1)
	{
		Tempsensor_Read(&temp);
		Control_fan( &ADC_value);
		
		Received_Data = SPI_transive(Trans_Data);
		
		if (Received_Data)
		{
			switch(Received_Data)
		{
			case  'A':
			DIO_SetPinValue(DIO_PORTD , DIO_PIN6 , DIO_PIN_HIGH);
			break;
			
			case  'a':
			DIO_SetPinValue(DIO_PORTD , DIO_PIN6 , DIO_PIN_LOW);
			break;
			
			case  'B':
			DC_Motor_SetDirection(CLOCKWISE);
			DC_Motor_Start();
			break;
			
			case  'b':
			DC_Motor_Stop();
			break;
			
			case  'C':
			Servo_Move(90);
			break;
			
			case  'c':
			Servo_Move(0);
			break;
			
			default:
			break;
		}
			
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
