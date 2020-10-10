/*
 * ADC.h
 *
 * Created: 8/15/2020 3:46:14 PM
 *  Author: Ibrahim
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "ATmega_Registers.h"
#include "BIT_MATH.h"
#include "ADC_Cfg.h"


#define		ADC_VRREF_AVCC			0
#define		ADC_VRREF_AREF			1
#define		ADC_VRREF_INTERNAL		2

#define		ADC_CHANNEL_0			0
#define		ADC_CHANNEL_1			1
#define		ADC_CHANNEL_2			2
#define		ADC_CHANNEL_3			3
#define		ADC_CHANNEL_4			4
#define		ADC_CHANNEL_5			5
#define		ADC_CHANNEL_6			6
#define		ADC_CHANNEL_7			7

#define		ADC_AUTO_TRIGGER		0
#define		ADC_FREE_RUNNING		1
#define		ADC_EXTERNAL_TRIG		2


#define		ADC_RIGHT_ADJUST		0
#define		ADC_LEFT_ADJUST			1

#define		ADC_PRESC_128			0
#define		ADC_PRESC_64			1
#define		ADC_PRESC_32			2
#define		ADC_PRESC_16			3
#define		ADC_PRESC_8				4
#define		ADC_PRESC_4				5
#define		ADC_PRESC_2				6



#define		ADC_INTERRUPT_ENABLE	0
#define		ADC_INTERRUPT_DISABLE	1



void ADC_Init(void);

void ADC_Read(uint16* value);

//void ADC_StartConversion(void);

//void ADC_CHANNEL_SELECTION(uint8 Channel);

#endif /* ADC_H_ */