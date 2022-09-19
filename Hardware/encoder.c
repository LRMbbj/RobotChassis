#include "encoder.h"
#include "tim.h"

#define FAULT_VAL 1000
//单个电机测试

//多电机
struct Encoder encoders[4] = {{&htim4, 40000}};
 
s32 Wheelspeed[4];
void EncoderInit(struct Encoder* ecd)
{
	
	HAL_TIM_Encoder_Start(ecd->htim, TIM_CHANNEL_ALL);
	
}

s32 EncoderGetValue(struct Encoder* ecd)
{
	return __HAL_TIM_GET_COUNTER(ecd->htim);
}

void EncoderGetSpeed()
{
	for(int i = 0; i < 4; i++)
	{
		u32 pos = __HAL_TIM_GET_COUNTER(encoders[i].htim);
		//if (pos < ecd->ppr / FAULT_VAL  || pos > ecd->ppr - ecd->ppr / FAULT_VAL) return 0;
		s32 spd = pos - encoders[i].ppr * __HAL_TIM_IS_TIM_COUNTING_DOWN(encoders[i].htim);
		__HAL_TIM_SET_COUNTER(encoders[i].htim, 0);
		Wheelspeed[i] = spd > encoders[i].ppr / 2 || spd < -encoders[i].ppr / 2 ? 0 : spd;
	}
   
   
}

s32 EncoderGetSpeed_1(struct Encoder* ecd)
{
    u32 pos = __HAL_TIM_GET_COUNTER(ecd->htim);
    //if (pos < ecd->ppr / FAULT_VAL  || pos > ecd->ppr - ecd->ppr / FAULT_VAL) return 0;
    s32 spd = pos - ecd->ppr * __HAL_TIM_IS_TIM_COUNTING_DOWN(ecd->htim);
    __HAL_TIM_SET_COUNTER(ecd->htim, 0);
    return spd > ecd->ppr / 2 || spd < -ecd->ppr / 2 ? 0 : spd;
}
