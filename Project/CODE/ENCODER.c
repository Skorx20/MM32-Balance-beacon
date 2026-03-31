#include "ENCODER.h"

void encoder_init(void)
{
	tim_encoder_init(encoder_L_TIM,encoder_L_A,encoder_L_B);
	tim_encoder_init(encoder_R_TIM,encoder_R_A,encoder_R_B);
}

int16 encoder_read(TIM_enum tim)
{
	int16 count;
	count = tim_encoder_get_count(tim);
	tim_encoder_rst(tim);
	
	return count;
}

int16 get_encoder(void)
{
	int16 speed;
	
	motor_left.speed = encoder_read(encoder_R_TIM);
  motor_left.speed = LPF_lst(motor_left.last_speed, motor_left.speed, 0.3f);
  motor_left.last_speed = motor_left.speed;
  
	motor_right.speed = -encoder_read(encoder_L_TIM);
  motor_right.speed = LPF_lst(motor_right.last_speed, motor_right.speed, 0.3f);
  motor_right.last_speed = motor_right.speed;

	speed = (motor_right.speed + motor_left.speed)/2;
	return	speed;
}
