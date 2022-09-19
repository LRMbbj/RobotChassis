#ifndef _SPEEDCONTROLLER_H
#define _SPEEDCONTROLLER_H
#include "pid.h"
#include "motor.h"
#include "encoder.h"

void SpdCtrlInit(struct PIDCircle *pid[4],struct Motor *motor[4]);
void SpdCtrlSetSpeed(int i,int j,int a);// i -> ����1speed j-> ����2 a-> ƫ�ƽǶ�

void Spd_test_forward();
void Spd_test_left();
void Spd_test_circle();

#endif

