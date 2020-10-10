/*
 * SPI.h
 *
 * Created: 10/7/2020 4:34:12 PM
 *  Author: Ibrahim
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "DIO.h"

void SPI_MasterInit(void);

void SPI_SlaveInit(void);

uint8 SPI_transive(uint8 data);

void SPI_InitTrans(void);

void SPI_TermTrans(void);






#endif /* SPI_H_ */