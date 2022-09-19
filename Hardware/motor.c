#include "motor.h"
#include <math.h>


const struct Motor motor[4] = {{&htim5, TIM_CHANNEL_2, 1000, GPIOF, GPIO_PIN_6, GPIO_PIN_7}};


void MotorInit(struct Motor *motor[4])
{
	for(int i = 0; i < 4; i++)
	{
		HAL_TIM_PWM_Start(motor[i]->htim, motor[i]->Channel);
	}
	
}

void MotorStatus(const struct Motor *motor, u8 state)
{
	
	if(state)
	{
		HAL_TIM_PWM_Start(motor->htim, motor->Channel);
		HAL_GPIO_WritePin(motor->DirGPIO, motor->DirA|motor->DirB, GPIO_PIN_SET );
	}
	else
	{
		HAL_TIM_PWM_Stop(motor->htim, motor->Channel);
		HAL_GPIO_WritePin(motor->DirGPIO, motor->DirA|motor->DirB, GPIO_PIN_RESET );
	}
	
}

void MotorSetGroupThruttle(int thrust[4])
{
	uint16_t ctrl;
	for (int i = 0; i < 4; i++)
	{
		if(thrust[i] >= 0)
		{
			HAL_GPIO_WritePin(motor[i].DirGPIO, motor[i].DirA, GPIO_PIN_SET );
			HAL_GPIO_WritePin(motor[i].DirGPIO, motor[i].DirB, GPIO_PIN_RESET );
			ctrl = thrust[i];
		}
		else
		{
			
			HAL_GPIO_WritePin(motor[i].DirGPIO, motor[i].DirA, GPIO_PIN_RESET );
			HAL_GPIO_WritePin(motor[i].DirGPIO, motor[i].DirB, GPIO_PIN_SET );
			ctrl = -thrust[i];
		}
		
		ctrl = ctrl > motor[i].Counter ? motor[i].Counter : ctrl;
	  
		__HAL_TIM_SET_COMPARE(motor[i].htim, motor[i].Channel, ctrl);
		
	}
}

void MotorStop()
{
	for(int i = 0; i < 4; i++)
	{
		
		HAL_GPIO_WritePin(motor[i].DirGPIO, motor[i].DirA|motor[i].DirB, GPIO_PIN_RESET );
	}
	
}

void MotorSetThruttle(int num,int thruttle)
{
	uint16_t ctrl;
	
	if(thruttle >= 0)
	{
		HAL_GPIO_WritePin(motor[num].DirGPIO, motor[num].DirA, GPIO_PIN_SET );
		HAL_GPIO_WritePin(motor[num].DirGPIO, motor[num].DirB, GPIO_PIN_RESET );
		ctrl = thruttle;
	}
	else
	{
		HAL_GPIO_WritePin(motor[num].DirGPIO, motor[num].DirA, GPIO_PIN_RESET );
		HAL_GPIO_WritePin(motor[num].DirGPIO, motor[num].DirB, GPIO_PIN_SET );
		ctrl = -thruttle;
	}
	
	ctrl = ctrl > motor[num].Counter ? motor[num].Counter : ctrl;
	
	__HAL_TIM_SET_COMPARE(motor[num].htim, motor[num].Channel, ctrl);
}


