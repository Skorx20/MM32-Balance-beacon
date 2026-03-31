#include "PID.h"

pid_structure pid_angspeed,pid_erect,pid_speed,pid_turn,pid_leftmotor,pid_rightmotor;

void pid_init(void)
{
	//	角速度环参数初始化 
	pid_angspeed.sum_error = 0;
	
	//直立环参数初始化
	pid_erect.sum_error = 0;

	//速度环参数初始化
	pid_speed.sum_error = 0;
}

//角速度环 PI
void angspeed(float set, float gyro)
{
	float error;
	error = gyro - set ;
		
	if(pid_angspeed.out >	20000)
	{
		if(error<=0)
    {
			pid_angspeed.sum_error += error;
    }
  }
  else if(pid_angspeed.out <	-20000)
  {
		if(error>=0)
    {
			pid_angspeed.sum_error += error;
    }
  }
  else
  {
		pid_angspeed.sum_error += error;
  }

	pid_angspeed.out = 10 * (pid_angspeed.kp * error + pid_angspeed.ki * pid_angspeed.sum_error);
}

//直立环 PD
void erect(float set, float angle, float gyro)
{
	float error;
  error = angle - set ; 

	pid_erect.out = pid_erect.kp * error + pid_erect.kd * gyro * 10;
//	pid_erect.out = LPF_lst(pid_erect.last_out, pid_erect.out, 0.3f);
//	pid_erect.last_out = pid_erect.out;
}

//速度环 PI
void speed(int16 set, int16 speed)
{
	static double	last_out;
	int16 error;
	error = speed - set;

	pid_speed.sum_error += error;
	Limit_data(&pid_speed.sum_error, 10000);
	
	pid_speed.out = pid_speed.kp * error + pid_speed.ki * pid_speed.sum_error;
	
//	pid_speed.out += pid_speed.kp * (pid_speed.error - pid_speed.last_error) + pid_speed.ki * pid_speed.error;
//	pid_speed.last_error = pid_speed.error;
	
	pid_speed.out = LPF_lst(last_out, pid_speed.out, 0.3f);		last_out = pid_speed.out;
}

//转向环 PD
void turn(int16 set, float gyro)
{
//	if(set >= -1 && set <= 1)
//		set = 0;

	pid_turn.out = pid_turn.kp * set + 100 * pid_turn.kd * gyro;
}
