/*
 * DC_Motor.h
 *
 * Created: 8/22/2020 6:27:40 PM
 *  Author: Ibrahim
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "Timer.h"
#include "DIO.h"

typedef enum
{
	CLOCKWISE,
	ANTI_CLOCKWISE
	
	}DC_Motor_DIR;

void DC_Motor_Init(void);

void DC_Motor_SetDirection(DC_Motor_DIR dir);

void DC_Motor_SetSpeed(uint8 speed);

//void DC_Motor_Start(uint8 speed , DC_Motor_DIR dir);

void DC_Motor_Start(void);

void DC_Motor_Stop(void);

#endif /* DC_MOTOR_H_ */