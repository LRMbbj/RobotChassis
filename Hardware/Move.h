#ifndef _MOVE_H
#define _MOVE_H
#include "motor.h"
#include "Tracker.h"
#include "pid.h"
#include "SpeedController.h"
#include "main.h"
typedef int16_t s16;
typedef int32_t s32;
typedef uint16_t u16;
typedef uint8_t u8;
void MoveOnTrack(int dir);//移动一个元位移
void MoveToNextLine(int dir, int data_XJ[2]);
void MoveToLine(int dir, int blocks,int data_XJ[2]);

#endif
