#include "CONTROL.h"

int16 expect_speed = 1200;
int16 expect_turn;

int16	actual_speed;

void TIM6_IRQHandler(void) //1ms
{
	int32 leftduty,rightduty;
	static uint8 flag_20ms=0; 

	uint32 state = TIM6->SR;
	
	mpudata_turn();

	if(mode_flag==1)
	{
		angspeed(pid_erect.out * 0.0001, gyro.y);
		
		if(flag_20ms==0)
		{			
			turn(expect_turn,gyro.z);
			Limit_data(&pid_turn.out, pid_angspeed.out);
		}
			
		leftduty  = pid_angspeed.out + pid_turn.out;
		rightduty = pid_angspeed.out - pid_turn.out;
		
		bt_send_double("speed",leftduty,7);
		
		motor_limit(&leftduty,&rightduty);
		motor_speed(leftduty,rightduty);
	}
	else
	{
		motor_speed(0,0);
		pid_init();
	}

	flag_20ms++;	if(flag_20ms==20)	flag_20ms=0;
	
	TIM6->SR &= ~state;
}

void TIM7_IRQHandler (void) //5ms
{
	static uint8 flag_10ms=0,flag_50ms=0;
	
	uint32 state = TIM7->SR;							// 读取中断状态

	if(flag_10ms==0)
	{
		actual_speed = get_encoder();   
		speed(expect_speed, actual_speed);
		
//		Limit_data(&pid_speed.out,150000);
	}
	
	if(flag_50ms==0)
	{
		beep_ring();
	}
	
	erect(pid_speed.out * 0.0001 + expect_angle, angle_now ,gyro.y);
	
	flag_10ms++;	if(flag_10ms==2)	flag_10ms=0;
	flag_50ms++;	if(flag_50ms==10)	flag_50ms=0;
	
	TIM7->SR &= ~state;																// 清空中断状态
}
