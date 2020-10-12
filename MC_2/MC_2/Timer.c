/*
 * Timer.c
 *
 * Created: 21/08/2020 06:33:49 PM
 *  Author: Ibrahim
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

void PWM1_Init(void)
{
	//setting port D pin5 direction to output
	
	DDRD |= 0x20;
	
	//selecting timer1 pwm mode 14 (fast pwm , controllable top(OCR1))
	
	TCCR1A |= 0x82; // setting bit 0 , bit 1 , bit 7    10000010	0x02
	TCCR1B |= 0x1c; // setting bit 2 , bit 3 , bit4	    00011100	0x18
	
	//assigning the value needed to achieve Frequency of generated wave of 50hz to ICR1
	
	ICR1 = 625; //1250 with 4m oscilator with clk/128 pre scaller ; 625 if in simulation 8m osclator
}


void PWM1_Generate(uint32 duty_cycle)
{
	// Duty Cycle = (OCR1A +1 / Top ) * 100
	
	OCR1A  = ((duty_cycle * 625) /100) -1 ;
}

void PWM1_Start(void)
{
	//giving clk access by selecting a presc
	
	TCCR1B |= 0x04 ; // bit 0, bit 1 , bit 3 of TCCR1B set to 1,0,0 to select presc 256
	
}