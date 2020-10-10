/*
 * Temprature_Sensor.c
 *
 * Created: 8/21/2020 4:27:07 PM
 *  Author: Ibrahim
 */ 

#include "Temprature_Sensor.h"

void Tempsensor_Init(void)
{
	ADC_Init();
}

void Tempsensor_Read(uint16* temp)
{
	//uint16 Analog_Value = 0;
	
	ADC_Read(temp);
	
	//	*Temp = Analog_Value * 10 ;
}