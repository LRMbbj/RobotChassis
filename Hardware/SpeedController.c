#include "SpeedController.h"
extern struct PIDCircle* pids[4];//�ĸ����������PID��
//��Ҫ�޸�
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
void SpdCtrlInit(struct PIDCircle *pid[4], struct Motor *motor[4]) //���¸��������PI��
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
//�ٶȱջ�����
void SpdCtrlSetMotor(int i, int j, int a)
{
    int FIX_SPEED_RANGE = 100;

    int low_boundary = 0;
    int high_boundary = 0;
    //	s32 currentspeed[4] ={0,0,0,0};
    float err[4] = {0, 0, 0, 0};
    u16 FIX_K = 1; //����k
    //����i���ٶ�

    //�޷�
    double low_boundary_i = i - FIX_SPEED_RANGE;
    double high_boundary_i = i + FIX_SPEED_RANGE;
    double low_boundary_j = j - FIX_SPEED_RANGE;
    double high_boundary_j = j + FIX_SPEED_RANGE;
    double low_boundary_a = a - FIX_SPEED_RANGE;
    double high_boundary_a = a + FIX_SPEED_RANGE;

    //limit(low_boundary_i,high_boundary_i);  limit(low_boundary_j,high_boundary_j); limit(low_boundary_a,high_boundary_a);

    EncoderGetSpeed();
    //�����ٶ�err
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
            MotorSetThruttle(low_boundary, i); //�ٶȹ��ͣ�����Ϊ��Сspeed
        else if (err[m] > FIX_SPEED_RANGE)
            MotorSetThruttle(high_boundary, i);
        //�������ٶ��ڣ�
        else
        {

            PIDUpdate(pids[m]);
            MotorSetThruttle(i, pids[m]->out); //����PID���������
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
    u16 FIX_K = 1; //����k
    //����i���ٶ�

    //�޷�
    double low_boundary_i = i - FIX_SPEED_RANGE;
    double high_boundary_i = i + FIX_SPEED_RANGE;
    double low_boundary_j = j - FIX_SPEED_RANGE;
    double high_boundary_j = j + FIX_SPEED_RANGE;
    double low_boundary_a = a - FIX_SPEED_RANGE;
    double high_boundary_a = a + FIX_SPEED_RANGE;

    //limit(low_boundary_i,high_boundary_i);  limit(low_boundary_j,high_boundary_j); limit(low_boundary_a,high_boundary_a);

    EncoderGetSpeed();
    //�����ٶ�err
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
            MotorSetThruttle(low_boundary, i); //�ٶȹ��ͣ�����Ϊ��Сspeed
        else if (err[m] > FIX_SPEED_RANGE)
            MotorSetThruttle(high_boundary, i);
        //�������ٶ��ڣ�
        else
        {

            PIDUpdate(pids[m]);
            MotorSetThruttle(i, pids[m]->out); //����PID���������
        }
    }
}
//
//�����С���˶����߼���֤
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
