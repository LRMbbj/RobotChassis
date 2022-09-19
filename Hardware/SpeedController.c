#include "SpeedController.h"
extern struct PIDCircle* pids[4];//四个驱动电机的PID环
//需要修改
/*
void limit(double low_boundary, double high_boundary)
{
    if (low_boundary < 1.0)
        low_boundary = low_boundary;
    else if (low_boundary > 999.0)
        low_boundary = 999.0;
    if (low_boundary < 1.0)
        high_boundary = high_boundary;
    else if (low_boundary > 999.0)
        high_boundary = 999.0;
}
*/
void SpdCtrlInit(struct PIDCircle *pid[4], struct Motor *motor[4]) //重新更新输出（PI）
{
    for (int i = 0; i < 4; i++)
    {
        PIDUpdate(pid[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        MotorSetThruttle(i, pid[i]->out);
    }
}
//速度闭环测试
void SpdCtrlSetMotor(int i, int j, int a)
{
    int FIX_SPEED_RANGE = 100;

    int low_boundary = 0;
    int high_boundary = 0;
    //	s32 currentspeed[4] ={0,0,0,0};
    float err[4] = {0, 0, 0, 0};
    u16 FIX_K = 1; //修正k
    //设置i向速度

    //限幅
    double low_boundary_i = i - FIX_SPEED_RANGE;
    double high_boundary_i = i + FIX_SPEED_RANGE;
    double low_boundary_j = j - FIX_SPEED_RANGE;
    double high_boundary_j = j + FIX_SPEED_RANGE;
    double low_boundary_a = a - FIX_SPEED_RANGE;
    double high_boundary_a = a + FIX_SPEED_RANGE;

    //limit(low_boundary_i,high_boundary_i);  limit(low_boundary_j,high_boundary_j); limit(low_boundary_a,high_boundary_a);

    EncoderGetSpeed();
    //更新速度err
    for (int m = 0; m < 4; m++)
    {
       
        if (m == 0)
        {
            err[m] = i - j + a * 10;
            PIDSetTarget(pids[m], err[m]);
        }
        if (m == 1)
        {
            err[m] = i + j + a * 10;
            PIDSetTarget(pids[m], err[m]);
        }
        if (m == 2)
        {
            err[m] = i - j - a * 10;
            PIDSetTarget(pids[m], err[m]);
        }
        if (m == 3)
        {
            err[m] = i + j - a * 10;
            PIDSetTarget(pids[m], err[m]);
        }
        if (err[m] < -FIX_SPEED_RANGE)
            MotorSetThruttle(low_boundary, i); //速度过低，设置为最小speed
        else if (err[m] > FIX_SPEED_RANGE)
            MotorSetThruttle(high_boundary, i);
        //在限制速度内：
        else
        {

            PIDUpdate(pids[m]);
            MotorSetThruttle(i, pids[m]->out); //更新PID环，并输出
        }
    }
}
void SpdCtrlSetSpeed(int i, int j, int a)
{
    int FIX_SPEED_RANGE = 100;

    int low_boundary = 0;
    int high_boundary = 0;
    //	s32 currentspeed[4] ={0,0,0,0};
    float err[4] = {0, 0, 0, 0};
    u16 FIX_K = 1; //修正k
    //设置i向速度

    //限幅
    double low_boundary_i = i - FIX_SPEED_RANGE;
    double high_boundary_i = i + FIX_SPEED_RANGE;
    double low_boundary_j = j - FIX_SPEED_RANGE;
    double high_boundary_j = j + FIX_SPEED_RANGE;
    double low_boundary_a = a - FIX_SPEED_RANGE;
    double high_boundary_a = a + FIX_SPEED_RANGE;

    //limit(low_boundary_i,high_boundary_i);  limit(low_boundary_j,high_boundary_j); limit(low_boundary_a,high_boundary_a);

    EncoderGetSpeed();
    //更新速度err
    for (int m = 0; m < 4; m++)
    {
       
        if (m == 0)
        {
            err[m] = i - j + a * 10;
            PIDSetTarget(pids[m], err[m]);
        }
        if (m == 1)
        {
            err[m] = i + j + a * 10;
            PIDSetTarget(pids[m], err[m]);
        }
        if (m == 2)
        {
            err[m] = i - j - a * 10;
            PIDSetTarget(pids[m], err[m]);
        }
        if (m == 3)
        {
            err[m] = i + j - a * 10;
            PIDSetTarget(pids[m], err[m]);
        }
        if (err[m] < -FIX_SPEED_RANGE)
            MotorSetThruttle(low_boundary, i); //速度过低，设置为最小speed
        else if (err[m] > FIX_SPEED_RANGE)
            MotorSetThruttle(high_boundary, i);
        //在限制速度内：
        else
        {

            PIDUpdate(pids[m]);
            MotorSetThruttle(i, pids[m]->out); //更新PID环，并输出
        }
    }
}
//
//电机和小车运动的逻辑验证
void Spd_test_forward()
{
    int val[4] = {300, 300, 300, 300};
    MotorSetGroupThruttle(val);
}

void Spd_test_left()
{
    int val[4] = {300, -300, 300, -300};
    MotorSetGroupThruttle(val);
}

void Spd_test_circle()
{
    int val[4] = {300, 300, -300, -300};
    MotorSetGroupThruttle(val);
}
