#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "tim.h"

typedef uint16_t u16;
typedef uint32_t u32;
typedef int32_t s32;

struct Encoder
{
	TIM_HandleTypeDef* htim;
	u16 ppr;
};

extern struct Encoder encoders[4];
extern s32 Wheelspeed[4];//// pidLF, pidRF, pidLB, pidRb;

void EncoderInit(struct Encoder* ecd);
s32 EncoderGetValue(struct Encoder* ecd);
void EncoderGetSpeed();
//µ¥¸ö²âÊÔ
s32 EncoderGetSpeed_1(struct Encoder* ecd);
#endif
