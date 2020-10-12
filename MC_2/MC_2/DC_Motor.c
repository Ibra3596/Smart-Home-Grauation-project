/*
 * DC_Motor.c
 *
 * Created: 8/22/2020 6:27:55 PM
 *  Author: Ibrahim
 */ 

#include "DC_Motor.h"

void DC_Motor_Init(void)
{
	//initializing the two pins that control the direction to output 
	
	DIO_SetPinDir(DIO_PORTC , DIO_PIN4 , DIO_PIN_OUTPUT); // high in clockwise
	DIO_SetPinDir(DIO_PORTC , DIO_PIN5 , DIO_PIN_OUTPUT); // low  in clockwise
	
	PWM0_Init();
}

void DC_Motor_SetDirection(DC_Motor_DIR dir)
{
	switch(dir)
	{
		case CLOCKWISE :
		DIO_SetPinValue(DIO_PORTC , DIO_PIN4 , DIO_PIN_HIGH);
		DIO_SetPinValue(DIO_PORTC , DIO_PIN5 , DIO_PIN_LOW);
		break;
		
		case ANTI_CLOCKWISE:
		DIO_SetPinValue(DIO_PORTC , DIO_PIN4 , DIO_PIN_LOW);
		DIO_SetPinValue(DIO_PORTC , DIO_PIN5 , DIO_PIN_HIGH);
		break;
		
		default:
		break;
		
	}
}

void DC_Motor_SetSpeed(uint8 speed)
{
	speed *=10; // range from 1 - 10 for simplicity 
	
	PWM0_Generate(speed);
}
/*
void DC_Motor_Start(uint8 speed , DC_Motor_DIR dir)
{
	DC_Motor_SetDirection(dir);
	speed *=10;
	PWM0_Generate(speed);
	PWM0_Start();
	
}
*/
void DC_Motor_Start(void)
{
	PWM0_Start();
}

void DC_Motor_Stop(void)
{
	// setting the two direction pins to high to stop inertia 
	
	DIO_SetPinValue(DIO_PORTC , DIO_PIN4 , DIO_PIN_HIGH); 
	DIO_SetPinValue(DIO_PORTC , DIO_PIN5 , DIO_PIN_HIGH);
}
