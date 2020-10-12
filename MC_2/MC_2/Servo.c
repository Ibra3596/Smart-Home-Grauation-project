/*
 * Servo.c
 *
 * Created: 9/2/2020 5:42:43 PM
 *  Author: Ibrahim
 */ 
#include "Servo.h"

void Servo_Init(void)
{
	PWM1_Init();
	
	PWM1_Start();
}

void Servo_Move(uint8 degree)
{
	uint16 duty_cycle = 0;
	
	duty_cycle =  5 + (0.36 * degree); //5 + ((1/36) * degree); //
	
	PWM1_Generate(duty_cycle);
	
}