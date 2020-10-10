/*
 * ADC.c
 *
 * Created: 8/15/2020 3:46:45 PM
 *  Author: Ibrahim
 */ 
#include "ADC.h"
#include <avr/interrupt.h>

volatile uint16 value = 0;

void ADC_Init(void)
{

	
	#if  ADC_VOLTAGE_REFERENCE	==	ADC_VRREF_AVCC
	CLR_BIT(ADMUX , 7);
	SET_BIT(ADMUX , 6);
	
	#elif ADC_VOLTAGE_REFERENCE	==	ADC_VRREF_AREF
	CLR_BIT(ADMUX , 7);
	CLR_BIT(ADMUX , 6);
	
	#endif
	
	#if  ADC_ADJUST				==	ADC_RIGHT_ADJUST
	
	CLR_BIT(ADMUX , 5);
	
	#elif  ADC_ADJUST			==	ADC_LEFT_ADJUST
	
	SET_BIT(ADMUX , 5);
	
	#endif

	#if  ADC_CHANNEL			==	ADC_CHANNEL_0

	ADMUX |= 0x00;
	
	#elif  ADC_CHANNEL			==	ADC_CHANNEL_1
	
	ADMUX |= 0x01;
	
	#elif  ADC_CHANNEL			==	ADC_CHANNEL_2
	
	ADMUX |= 0x02;
	
	#elif  ADC_CHANNEL			==	ADC_CHANNEL_3
	
	ADMUX |= 0x03;
	
	#elif  ADC_CHANNEL			==	ADC_CHANNEL_4
	
	ADMUX |= 0x04;
	
	#elif  ADC_CHANNEL			==	ADC_CHANNEL_5
	
	ADMUX |= 0x05;
	
	#elif  ADC_CHANNEL			==	ADC_CHANNEL_6
	
	ADMUX |= 0x06;
	
	#elif  ADC_CHANNEL			==	ADC_CHANNEL_7
	
	ADMUX |= 0x07;
	
	#endif

	#if	 ADC_CONVERSION_TRIGGER	==	ADC_AUTO_TRIGGER
	
	SET_BIT(ADCSRA , 5);
	
	#endif

	#if	 ADC_PRESCALER				==	ADC_PRESC_128
	
	ADCSRA |= 0x07;
	
	#elif	 ADC_PRESCALER			==	ADC_PRESC_64
	
	ADCSRA |= 0x06;
	
	#elif	 ADC_PRESCALER			==	ADC_PRESC_32
	
	ADCSRA |= 0x05;
	
	#elif	 ADC_PRESCALER			==	ADC_PRESC_16
	
	ADCSRA |= 0x04;
	
	#elif	 ADC_PRESCALER			==	ADC_PRESC_8
	
	ADCSRA |= 0x03;
	
	#elif	 ADC_PRESCALER			==	ADC_PRESC_4
	
	ADCSRA |= 0x02;
	
	#elif	 ADC_PRESCALER			==	ADC_PRESC_2
	
	ADCSRA |= 0x01;
	
	#endif
	

	#if	 ADC_INTERRUPT_SATATE	==	ADC_INTERRUPT_DISABLE
	
	CLR_BIT(ADCSRA , 3);
	
	#elif ADC_INTERRUPT_SATATE	==	ADC_INTERRUPT_ENABLE
	
	SET_BIT(ADCSRA , 3);
	
	#endif
	
	
	//ADC Enable
	SET_BIT(ADCSRA , 7);

}





void ADC_Read(uint16* value)
{
	uint16 Digital_value = 0;
	
	//start conversion
	SET_BIT(ADCSRA , 6);
	
	#if ADC_INTERRUPT_SATATE == ADC_INTERRUPT_DISABLE
	
	while(!GET_BIT(ADCSRA ,4)); //Flag is not set(1) yet (pooling)
	
	Digital_value = ADC_Adjust;
	
	*value = ((Digital_value * 500) / 1024);
	//*value = Digital_value;
	#endif
	
}


ISR(ADC_vect)
{
	value = ((ADC_Adjust * 500) / 1024);
}