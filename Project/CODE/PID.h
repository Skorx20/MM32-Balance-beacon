#ifndef _PID_h
#define _PID_h

#include "common.h"
#include "headfile.h"

#define None 0
#define Exist 1
#define Right 2
#define Left 3
#define Forward 4

typedef struct
{
  uint16 kp; //P
  uint16 ki; //I
  uint16 kd; //D
  double out; //pidÊä³ö
  double sum_error; //Îó²î×ÜºÍ
}pid_structure;

extern pid_structure pid_angspeed,pid_erect,pid_speed,pid_turn,pid_turn,pid_leftmotor,pid_rightmotor;

void pid_init(void);
void angspeed(float set, float gyro);
void erect(float set, float angle, float gyro);
void speed(int16 set, int16 speed);
void turn(int16 set, float gyro);

#endif
