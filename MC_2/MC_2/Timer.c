/*
 * CFile1.c
 *
 * Created: 21/08/2020 06:33:49 ã
 *  Author: Ali
 */ 


#include "Timer.h"
#include <avr/interrupt.h>


#define  NULL  ((void*)(0))

void (*ptr)(void) = NULL ;


uint8    Init_Value = 0;
uint32   Number_OVRflows = 0;


void Timer0_Init(void)
{
	
	TCCR0 |= 0x00;
	
	TIMSK |= 0x01;
	
	SREG |= 0x80;
	
}

void Timer0_Start(void)
{
	TCCR0 |= 0x05;
}

void Timer0_Stop(void)
{
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
}



void Timer0_SetDelay(uint32 Delay_Ms)
{
	
	uint8 Tick_Time = (1024 / 8) ;
	
	uint32 Total_Ticks = (Delay_Ms * 1000) / Tick_Time ;
	
	Number_OVRflows = Total_Ticks / 256 ;
	
	Init_Value  =   256 - (Total_Ticks % 256) ;
	
	TCNT0 = Init_Value ;
	
	Number_OVRflows++;
	
}



void Timer1_Init(void)
{
	TCCR1B |= 0X08 ;
	TIMSK  |= 0X10;
	SREG   |= 0X80;
}

void Timer1_Start(void)
{
	TCCR1B |= 0X05 ;
}

void Timer1_Stop(void)
{
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}


void Timer1_SetDelay(uint32 Delay_Ms)
{
	
	if(Delay_Ms <= 4000)
	{
		uint8 Tick_Time = 1024 / 16;
		
		uint32 Num_Ticks = (Delay_Ms * 1000) / Tick_Time ;
		
		OCR1A = Num_Ticks - 1;
	}
	
}




void Set_CallBack(void(*p)(void))
{
	
	ptr = p ;
	
}



ISR(TIMER0_OVF_vect)
{
	static uint32 cnt = 0;
	
	cnt++;
	
	if(cnt == Number_OVRflows)
	{
		TCNT0 = Init_Value;
		
		cnt = 0;
		
		(*ptr)();
	}
}



ISR(TIMER1_COMPA_vect)
{
	static counter = 0;
	
	counter++;
	
	if(counter == 1)
	{
		counter = 0;
		
		(*ptr)();
	}
}


void PWM0_Init(void)
{
	DDRB |= 0x08;
	
	TCCR0 |= 0x68;
	
}


void PWM0_Generate(uint16 Duty_Cycle)
{
	OCR0 = ((Duty_Cycle * 256 ) /100 ) - 1;
}



void PWM0_Start(void)
{
	
	TCCR0 |= 0x01 ;
	
}