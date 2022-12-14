#ifndef __PID_H__
#define __PID_H__

#include "tim.h"
#include "encoder.h"
#include <math.h>

#define PID_NUM 2

#define PID_STATE_ACTIVE 1
#define PID_STATE_DEACTIVE 0

typedef int16_t s16;
typedef int32_t s32;
typedef uint16_t u16;
typedef uint8_t u8;

struct PIDCircle
{
    float kp, ki, kd;
    s32 tgt;
    s16 i_band, i_limit;
    s16 sum_limit;
    s32 *cur;
    u16 maxE;
    //void *obj;
    //void(*func)(void*,int16_t);
    
    s16 p_out, i_out, d_out;
    s16 e;
    s16 last_cur;
    s16 out;
    u8 isOn;
};


extern  struct PIDCircle* pids[4];//四个驱动电机的PID环
extern  struct PIDCircle* PID_Carangel;//角度PID
extern  struct PIDCircle* PID_Carpos;//水平位置PID
extern int abs(int);
extern int data_XJ[2];
void PIDSetTarget(struct PIDCircle* pid, s32 target);

void PIDInit();
void PIDReset(struct PIDCircle* pid);
void PIDUpdate(struct PIDCircle* pid);
void PIDSetState(struct PIDCircle* pid, u8 state);

s16 PIDGetValue(struct PIDCircle* pid );

#endif
