#ifndef _MPU_h
#define _MPU_h

#include "common.h"
#include "headfile.h"

#define rad 57.30 //角度化弧度的系数
#define gyro_sensitivity 16.40
#define acc_sensitivity 4096

typedef struct
{
  float x;
	float y;
	float z;
	float x_last;
	float y_last;
	float z_last;
}data_structure;

extern data_structure gyro,acc;

extern float expect_angle;		// 期望角
extern float angle_now;
extern float angle_deviation;

float Kalman_Filter(float acc,float gyro);

void mpudata_turn(void);

#endif
