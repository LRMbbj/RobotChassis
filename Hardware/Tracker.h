#ifndef _TRACKER_H
#define _TRACKER_H
#include "gpio.h"

struct Sensor
{
	GPIO_TypeDef* GPIO_Port;
	uint32_t pin[4];// 针脚
	
};


//extern struct Sensor Sensors[4];//四个方向四个sensor 0, 1, 2, 3对应f r b l


void TrackInit();
void TrackGetBias(int dir,  int data[2]);//传入1 2 3 4 -> f r b l ,获得不同方向的值 穿入temp获取两个偏移值


#endif

