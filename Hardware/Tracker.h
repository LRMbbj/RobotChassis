#ifndef _TRACKER_H
#define _TRACKER_H
#include "gpio.h"

struct Sensor
{
	GPIO_TypeDef* GPIO_Port;
	uint32_t pin[4];// ���
	
};


//extern struct Sensor Sensors[4];//�ĸ������ĸ�sensor 0, 1, 2, 3��Ӧf r b l


void TrackInit();
void TrackGetBias(int dir,  int data[2]);//����1 2 3 4 -> f r b l ,��ò�ͬ�����ֵ ����temp��ȡ����ƫ��ֵ


#endif

