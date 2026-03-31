#include "MOTOR.h"

#define PWM_LIMIT_MAX 30000
#define PWM_LIMIT_MIN -30000
#define PWM_DEAD_VAL_LEFT_N 2400
#define PWM_DEAD_VAL_LEFT_P 2600
#define PWM_DEAD_VAL_RIGHT_N 2500
#define PWM_DEAD_VAL_RIGHT_P 2600

motor_structure motor_left,motor_right;

void motor_init(void)
{
	pwm_init(motor_TIM,motor_L_A,10000,0);
	pwm_init(motor_TIM,motor_L_B,10000,0);
	pwm_init(motor_TIM,motor_R_A,10000,0);
	pwm_init(motor_TIM,motor_R_B,10000,0);
}

void motor_limit(int32 *leftduty, int32 *rightduty)
{
	if(*leftduty<500 && *leftduty>-500)		*leftduty = 0;
	if(*rightduty<500 && *rightduty>-500)	*rightduty = 0;
	
	if(*leftduty > 0)											*leftduty += PWM_DEAD_VAL_LEFT_N;
	else if(*leftduty < 0)								*leftduty -= PWM_DEAD_VAL_LEFT_P;
	
	if(*rightduty > 0)										*rightduty += PWM_DEAD_VAL_RIGHT_N;
	else if(*rightduty < 0)								*rightduty -= PWM_DEAD_VAL_RIGHT_P;
	
	if(*leftduty > PWM_LIMIT_MAX)					*leftduty = PWM_LIMIT_MAX;
	else if(*leftduty < PWM_LIMIT_MIN)		*leftduty = PWM_LIMIT_MIN;
	
	if(*rightduty > PWM_LIMIT_MAX)				*rightduty = PWM_LIMIT_MAX;
	else if(*rightduty < PWM_LIMIT_MIN)		*rightduty = PWM_LIMIT_MIN;
}

void motor_speed(int16 leftduty,int16 rightduty)
{
	if(leftduty>0)
	{
		pwm_duty_updata(motor_TIM,motor_L_A,leftduty);
		pwm_duty_updata(motor_TIM,motor_L_B,0);
	}
	else
	{
		pwm_duty_updata(motor_TIM,motor_L_A,0);
		pwm_duty_updata(motor_TIM,motor_L_B,-1*leftduty);
	}
	if(rightduty>0)
	{
		pwm_duty_updata(motor_TIM,motor_R_A,rightduty);
		pwm_duty_updata(motor_TIM,motor_R_B,0);
	}
	else
	{
		pwm_duty_updata(motor_TIM,motor_R_A,0);
		pwm_duty_updata(motor_TIM,motor_R_B,-1*rightduty);
	}
}
