/*
 * Temprature_Sensor.h
 *
 * Created: 8/15/2020 3:47:57 PM
 *  Author: Ibrahim
 */ 


#ifndef TEMPRATURE_SENSOR_H_
#define TEMPRATURE_SENSOR_H_

#include "ADC.h"

void Tempsensor_Init(void);


void Tempsensor_Read(uint16* temp);





#endif /* TEMPRATURE_SENSOR_H_ */