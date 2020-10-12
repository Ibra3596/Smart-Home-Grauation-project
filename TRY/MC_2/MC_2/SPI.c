/*
 * SPI.c
 *
 * Created: 7/10/2020 4:33:56 PM
 *  Author: Ibrahim
 */ 
#include "SPI.h"


#define SPI_Interupt_Enable		1
#define SPI_Interupt_Disable    0

#define SPI_Interupt_State		SPI_Interupt_Enable


uint8 volatile SPI_TXData = 0;
uint8 volatile SPI_RXData = 0;

void SPI_MasterInit(void)
{	
	DIO_SetPinDir(SPI_PORT, MISO_PIN , DIO_PIN_INPUT);
	DIO_SetPinDir(SPI_PORT, MOSI_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(SPI_PORT, SS_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(SPI_PORT, SCK_PIN , DIO_PIN_OUTPUT);
	
	SPI->SPCR.SPR0 = 1;
	SPI->SPCR.SPR1 = 1;		//SPI0 , SPI1, =11 set prescaler of  osc/128
	SPI->SPCR.MSTR = 1;		//select as a Master
	SPI->SPCR.SPE  = 1;		//enable SPI
	SPI->SPCR.SPIE = 1;		// enable SPI interrupt
	
	SREG |=0x80;
}

void SPI_SlaveInit(void)
{	
	DIO_SetPinDir(SPI_PORT, MISO_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(SPI_PORT, MOSI_PIN , DIO_PIN_INPUT);
	DIO_SetPinDir(SPI_PORT, SS_PIN , DIO_PIN_INPUT);
	DIO_SetPinDir(SPI_PORT, SCK_PIN , DIO_PIN_INPUT);
	
	SPI->SPCR.SPR0 = 0;
	SPI->SPCR.SPR1 = 0;
	SPI->SPCR.CPHA = 0;
	SPI->SPCR.CPOL = 0;
	SPI->SPCR.MSTR = 0;
	SPI->SPCR.DORD = 0;
	SPI->SPCR.SPE  = 1;
	
	SPI->SPCR.SPIE = 1;		// enable SPI interrupt
	
	SREG |=0x80;
}

uint8 SPI_transive(uint8 tx_data)
{
	uint8 rec_data = 0;
	
	SPI->SPDR = tx_data;
	
	#if SPI_Interupt_State == SPI_Interupt_Disable
	
	while(GET_BIT(SPI->SPSR , 7) == 0);
	rec_data = SPI->SPDR;
	
	#else
	
	rec_data = SPI->SPDR;
	
	#endif
	
	return rec_data;
	
}

void SPI_InitTrans(void)
{
	DIO_SetPinValue(SPI_PORT , SS_PIN , DIO_PIN_LOW);
	
}

void SPI_TermTrans(void)
{
	DIO_SetPinValue(SPI_PORT , SS_PIN , DIO_PIN_HIGH);
	
}

#include <avr/interrupt.h>

ISR (SPI_STC_vect)
{
	SPI_RXData = SPI_SPDR;
}