#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "tim.h"

#define MOTOR_STATUS_ACTIVE 1
#define MOTOR_STATUS_DEACTIVE 0

typedef uint8_t u8;

struct Motor
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
	uint32_t Counter;
	GPIO_TypeDef *DirGPIO;
	uint16_t DirA;
	uint16_t DirB;
};

extern const struct Motor motor[4];
void MotorStatus(const struct Motor *motor, u8 state);//¿ØÖÆ×´Ì¬
void MotorInit(struct Motor *motor[4]);
void MotorSetGroupThruttle(int thrust[4]);
void MotorSetThruttle(int num,int thruttle);
void MotorStop();

#endif
