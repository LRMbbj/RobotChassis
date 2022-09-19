
#include "pid.h"
#include "host.h"
#include "main.h"
#include <math.h>
#include "motor.h"
struct PIDCircle* pids[4]={0};//ËÄ¸öÇý¶¯µç»úµÄPID»·
struct PIDCircle* PID_Carangel;//½Ç¶ÈPID
struct PIDCircle* PID_Carpos;//Ë®Æ½Î»ÖÃPID
// pidLF, pidRF, pidLB, pidRb 0 1 2 3 ;
void PIDSetTarget(struct PIDCircle* pid, s32 target)
{
    pid->tgt = target;
}

s32 limit(s32 val, s32 tgt)
{
    
    if( abs(val) > tgt )
        return val > 0 ? tgt : -tgt;
    else
        return val;
    
}

//s32 Normalize(s32 val, s32 max)
//{
//    return (val + max * 5) % (max * 2) - max;
//}

void PIDInit()
{
	//test
	// pid LF环
    pids[0]->kp = 1; 
    pids[0]->ki = 0.1; 
    pids[0]->kd = 0; 
    pids[0]->tgt  = 0;
    pids[0]->i_band = 20;
    pids[0]->i_limit  = 200;
    pids[0]->sum_limit = 400;
    pids[0]->cur =  &Wheelspeed[0];
    //pids[0]->cur =  &Wheelspeed[0];
    PIDReset(pids[0]);
    
    
   
    // pid RF环
    pids[1]->kp = 1;
    pids[1]->ki = 0.1; 
    pids[1]->kd = 0;
    pids[1]->tgt  = 0;
    pids[1]->i_band = 20;
    pids[1]->i_limit  = 200;
    pids[1]->sum_limit = 400;
    
    pids[1]->cur =  &Wheelspeed[1];
    PIDReset(pids[1]);
	
	//pid LB
	pids[2]->kp = 1;
    pids[2]->ki = 0.1;
    pids[2]->kd = 0; 
    pids[2]->tgt  = 0;
    pids[2]->i_band = 20;
    pids[2]->i_limit  = 200;
    pids[2]->sum_limit = 400;
    
    pids[2]->cur =  &Wheelspeed[2];
    PIDReset(pids[2]);
	//pid RB
	pids[3]->kp = 1;
    pids[3]->ki = 0.1;
    pids[3]->kd = 0; 
    pids[3]->tgt  = 0;
    pids[3]->i_band = 20;
    pids[3]->i_limit  = 200;
    pids[3]->sum_limit = 400;
    
    pids[3]->cur =  &Wheelspeed[3];
    PIDReset(pids[3]);
	
	//PID_Carangel
	
    PID_Carangel->kp = 1; 
    PID_Carangel->ki = 0.1; 
    PID_Carangel->kd = 0; 
    PID_Carangel->tgt  = 0;
    PID_Carangel->i_band = 20;
    PID_Carangel->i_limit  = 200;
    PID_Carangel->sum_limit = 400;
    PID_Carangel->cur = &data_XJ[1];
    PIDReset(PID_Carangel);
	
	//PID_CarPos
	
   PID_Carpos->kp = 1; 
   PID_Carpos->ki = 0.1; 
   PID_Carpos->kd = 0; 
   PID_Carpos->tgt  = 0;
   PID_Carpos->i_band = 20;
   PID_Carpos->i_limit  = 200;
   PID_Carpos->sum_limit = 400;
    
   PID_Carpos->cur =  &data_XJ[0];
    PIDReset(PID_Carpos);
}

void PIDReset(struct PIDCircle* pid)
{
    
    pid->e = 0;
    pid->last_cur = 0;
    pid->out = 0;
    pid->p_out = 0;
    pid->i_out = 0;
    pid->d_out = 0;
    
}

void PIDUpdate(struct PIDCircle* pid)
{
    
    pid->e = *(pid->cur) - pid->tgt;
    
    pid->d_out = pid->kd * (*(pid->cur) - pid->last_cur); //计算d
    pid->last_cur = *(pid->cur);
    
    pid->p_out = pid->kp * pid->e;
    
    if( abs( pid->e ) > pid->i_band && pid->i_band > 0 )
        pid->i_out = 0;
    else
        pid->i_out += pid->ki * pid->e;
    
    pid->i_out = limit(pid->i_out, pid->i_limit );
    
    pid->out = pid->p_out + pid->i_out + pid->d_out;
    
    pid->out = limit(pid->out, pid->sum_limit);
    
    //pid->func(pid ->obj, pid->out);
    
}


void PIDSetState(struct PIDCircle* pid, u8 state)
{
    pid->isOn = state;
    if (state == PID_STATE_DEACTIVE) PIDReset(pid);
}


s16 PIDGetValue(struct PIDCircle* pid )
{
	pid->e = *(pid->cur) - pid->tgt;
    
    pid->d_out = pid->kd * (*(pid->cur) - pid->last_cur); //计算d
    pid->last_cur = *(pid->cur);
    
    pid->p_out = pid->kp * pid->e;
    
    if( abs( pid->e ) > pid->i_band && pid->i_band > 0 )
        pid->i_out = 0;
    else
        pid->i_out += pid->ki * pid->e;
    
    pid->i_out = limit(pid->i_out, pid->i_limit );
    
    pid->out = pid->p_out + pid->i_out + pid->d_out;
    
    pid->out = limit(pid->out, pid->sum_limit);
	
	return pid->out;
}



/*
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim7)
    {
        for (u8 i = 0; i < PID_NUM; i++)
        {
            if (pids[0]->isOn) 
            {
                PIDUpdate(pids[0]);
                //(pids[i]->func)(pids[i]->obj, pids[i]->out);
							  MotorSetThruttle(0, pids[0]->out);
            }
        }
    
       
    }
}
*/

