#ifndef _MOTOR_h
#define _MOTOR_h

#include "common.h"
#include "headfile.h"

#define motor_TIM TIM_5
#define motor_L_A TIM_5_CH2_A01
#define motor_L_B TIM_5_CH1_A00
#define motor_R_A TIM_5_CH3_A02
#define motor_R_B TIM_5_CH4_A03

typedef struct
{
	int16 speed;
  int16 last_speed;
}motor_structure;

extern motor_structure motor_left,motor_right;

void motor_init(void);
void motor_limit(int32 *leftduty,int32 *rightduty);
void motor_speed(int16 leftduty,int16 rightduty);

#endif
