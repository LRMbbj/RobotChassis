#include "Move.h"
int i_normal = 100;
int j_normal = 100;
extern struct PIDCircle* pids[4];//四个驱动电机的PID环
extern struct PIDCircle* PID_Carangel;//角度PID
extern struct PIDCircle* PID_Carpos;//水平位置PID
void CarForwardPID(int dir)
{
	PIDSetTarget(PID_Carangel, 0);
	PIDSetTarget(PID_Carpos, 0);
	int Angelout = PIDGetValue(PID_Carangel);
	int Posout = PIDGetValue(PID_Carpos);
	SpdCtrlSetSpeed(i_normal ,j_normal + Posout,Angelout);
}



void MoveOnTrack(int dir)//1,2,3,4对应forward,back,link,right
{
	uint16_t speed = 300;//定义一个驱动速度
	int thrust[4];
	if(dir == 1)
	{
		for(int i = 0; i < 4; i++)
		{
			thrust[i] = speed;
		}
		MotorSetGroupThruttle(thrust);
		//delay_ms(10);//到时候加个时延函数
		for(int i = 0; i < 4; i++)
		{
			thrust[i] = 0;
		}
		MotorSetGroupThruttle(thrust);
		
	}
	
	if(dir == 2)
	{
		for(int i = 0; i < 4; i++)
		{
			thrust[i] = -speed;
		}
		MotorSetGroupThruttle(thrust);
//		delay_ms(10);
		for(int i = 0; i < 4; i++)
		{
			thrust[i] = 0;
		}
		MotorSetGroupThruttle(thrust);
	}
	
	if(dir == 3)
	{
		thrust[2] = thrust[0] = speed;
		thrust[3] = thrust[1] = -speed;
		MotorSetGroupThruttle(thrust);
//		delay_ms(10);
		for(int i = 0; i < 4; i++)
		{
			thrust[i] = 0;
		}
		MotorSetGroupThruttle(thrust);
	}
	
	if(dir == 4)
	{
		thrust[2] = thrust[0] = -speed;
		thrust[3] = thrust[1] = speed;
		MotorSetGroupThruttle(thrust);
//		delay_ms(10);
		for(int i = 0; i < 4; i++)
		{
			thrust[i] = 0;
		}
		MotorSetGroupThruttle(thrust);
	}
	
}



void MoveToNextLine(int dir, int data_XJ[2])
{
	
		u16 Flag_passPoint = 0;//路过中心点
		while(Flag_passPoint == 0)
		{
		    
			TrackGetBias(dir + 1, data_XJ);//获得右手侧的误差
			if(data_XJ[1] == 0 && data_XJ[0] != 0 )
				Flag_passPoint = 1;
			
			CarForwardPID(dir);
		}
		
		MotorStop();
		TrackGetBias(dir,data_XJ);
		
		
		while(data_XJ[1] > 0)//如果通过了线需要顺时针旋转
		{
			SpdCtrlSetSpeed(100,100 ,-1);
			TrackGetBias(dir,data_XJ);
		}
		
		while(data_XJ[1] < 0)//如果通过了线需要逆时针旋转
		{
			SpdCtrlSetSpeed(100,100,1);
			TrackGetBias(dir,data_XJ);
		}
}

void MoveToLine(int dir, int blocks,int data_XJ[2])
{
	
	
		while(blocks != 0)
		{
			u16 Flag_passPoint = 0;//路过中心点
			while(Flag_passPoint == 0)
			{
				TrackGetBias(dir + 1, data_XJ);//获得右手侧的误差
				if(data_XJ[1] == 0 && data_XJ[0] != 0 )
					Flag_passPoint = 1;
			
				CarForwardPID(dir);
			}
			blocks--;
		}
		
		
		MotorStop();
		TrackGetBias(dir,data_XJ);
		
		
		while(data_XJ[1] > 0)//如果通过了线需要顺时针旋转
		{
			SpdCtrlSetSpeed(100,100 ,-1);
			TrackGetBias(dir,data_XJ);
		}
		
		while(data_XJ[1] < 0)//如果通过了线需要逆时针旋转
		{
			SpdCtrlSetSpeed(100,100,1);
			TrackGetBias(dir,data_XJ);
		}
	
	
}





