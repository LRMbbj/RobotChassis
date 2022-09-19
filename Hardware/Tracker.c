#include "Tracker.h"
struct Sensor Sensors[4];

int getval(int states[4])
{
    int f;
    if ((states[1] == 0) && (states[2]==0))
        f = 0;
		else if ((states[0]== 0) && (states[1]==0))
        f = -2;
    else if ((states[2]==0) && (states[3]==0))
        f = 2;
    else if (states[1] == 0)
        f = -1;
    else if (states[2] == 0)
        f = 1;
    
    else if (states[0] == 0)
        f = -3;
    else if (states[3] == 0)
        f = 3;
    else
        f = 0;
    return f;
}

void TrackInit()
{
  Sensors[0].GPIO_Port = GPIOF;
  Sensors[0].pin[0]= track1_Pin;
  Sensors[0].pin[1]= track2_Pin;
  Sensors[0].pin[2]= track3_Pin;
  Sensors[0].pin[3]= track4_Pin;
  
  Sensors[1].GPIO_Port = GPIOE;
  Sensors[1].pin[0]= tracK_b1_Pin;
  Sensors[1].pin[1]= tracK_b2_Pin;
  Sensors[1].pin[2]= tracK_b3_Pin;
  Sensors[1].pin[3]= tracK_b4_Pin;
  
}
void TrackGetBias(int dir, int data[2]) //f,b,l,r -> 1,2,3，4
{
    int states[4];    //前sensor的状态
    int states_re[4];  //后置的sensor状态
	
    for (int i = 0; i < 4; i++) // 读取前方向sensor状态
    {
			if(HAL_GPIO_ReadPin(Sensors[dir - 1].GPIO_Port, Sensors[dir - 1].pin[i]) == GPIO_PIN_SET)
				states[i] = 1 ;
			else 
				states[i] = 0;
    }
		//读取对应sensor状态
    if (dir == 1)//向前
    {
        for (int i = 0; i < 4; i++) // 读取一次sensor状态
        {
					if(HAL_GPIO_ReadPin(Sensors[1].GPIO_Port, Sensors[1].pin[i])  )
						states_re[i] = 1;
					else
						states_re[i] = 0;
        }
    }
    if (dir == 2)//向后
    {
        for (int i = 0; i < 4; i++) // 读取一次sensor状态
        {
					if(HAL_GPIO_ReadPin(Sensors[0].GPIO_Port, Sensors[0].pin[i]) )
						states_re[i] = 1;
					else
						states_re[i] = 0;
				}
    }
    if (dir == 3)//向左
    {
        for (int i = 0; i < 4; i++) // 读取一次sensor状态
        {
			if(HAL_GPIO_ReadPin(Sensors[3].GPIO_Port, Sensors[3].pin[i]) )
				states_re[i] = 1;
			else
				states_re[i] = 0;
        }
    }
    if (dir == 4)//向右
    {
        for (int i = 0; i < 4; i++) // 读取一次sensor状态
        {
			if(HAL_GPIO_ReadPin(Sensors[2].GPIO_Port, Sensors[2].pin[i])  )
				states_re[i] = 1;
			else
				states_re[i] = 0;
        }
    }
    int f = getval(states);
    int b = getval(states_re); // 取得前后的信号
    //进行融合
    data[0] = (f - b) / 2;//水平
    data[1] = (f + b) / 2;//角度
		//data[0] = f;
		//data[1] = b;
}
