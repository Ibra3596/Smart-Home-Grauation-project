/*
 * SPI.c
 *
 * Created: 10/7/2020 4:33:56 PM
 *  Author: Ibrahim
 */ 
#include "SPI.h"

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
}

uint8 SPI_transive(uint8 tx_data)
{
	uint8 rec_data = 0;
	
	SPI->SPDR = tx_data;
	
	while(GET_BIT(SPI->SPSR , 7) == 0);
	
	rec_data = SPI->SPDR;
	
}

void SPI_InitTrans(void)
{
	DIO_SetPinValue(SPI_PORT , SS_PIN , DIO_PIN_LOW);
}

void SPI_TermTrans(void)
{
	DIO_SetPinValue(SPI_PORT , SS_PIN , DIO_PIN_HIGH);
}