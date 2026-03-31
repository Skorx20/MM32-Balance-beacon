#include "MPU.h"

#define rad 57.30 //角度化弧度的系数
#define gyro_sensitivity 16.40
#define acc_sensitivity 4096

float expect_angle;		// 期望角
float angle_now;		//	当前角度
float angle_deviation;

data_structure motor,gyro,acc;

//角度,角速度,加速度换算(角速度单位化为弧度每秒，加速度单位化为9.8米每平方秒)
void mpudata_turn(void)
{
	float ACC_a,GYR_a;
	static float angle_last;

	get_icm20602_accdata();
	get_icm20602_gyro();
	
	gyro.x = LPF_lst(gyro.x_last,(float)icm_gyro_x,0.3f);	gyro.x_last=gyro.x;
	gyro.y = LPF_lst(gyro.y_last,(float)icm_gyro_y,0.3f);	gyro.y_last=gyro.y;
	gyro.z = LPF_lst(gyro.y_last,(float)icm_gyro_z,0.3f);	gyro.z_last=gyro.z;
	
	gyro.x = gyro.x/(gyro_sensitivity*rad);
	gyro.y = gyro.y/(gyro_sensitivity*rad);
	gyro.z = gyro.z/(gyro_sensitivity*rad);
	
	acc.x = LPF_lst(acc.x_last,(float)icm_acc_x,0.3f);	acc.x_last=acc.x;
	acc.z = LPF_lst(acc.z_last,(float)icm_acc_z,0.3f);	acc.z_last=acc.z;
	
	acc.x = acc.x/(acc_sensitivity*rad);
	acc.z = acc.z/(acc_sensitivity*rad);

	ACC_a = atan(acc.x/acc.z)*rad;
	GYR_a = gyro.x * 0.002; //0.005为检测的时间间隔
	
//	angle_now = Kalman_Filter(ACC_a,gyro.x);		// 卡尔曼滤波
	
	angle_now =LPF_lst((angle_last + GYR_a), ACC_a,0.3f);	//t为高频部分权重，t越大，灵敏度越高
	angle_last = angle_now;
	
	angle_now += angle_deviation;
}


//	卡尔曼滤波
float Kalman_Filter(float acc,float gyro) 		
{
	//	Q_angle表示加速度计过程噪声协方差、Q_bias表示陀螺仪过程噪声协方差、R_measure表示测量噪声协方差、P表示误差协方差矩阵
	const float Q_angle=0.001, Q_gyro=0.003, R_measure=0.5, dt=0.005;
	static float angle;
	static float Q_bias;	
	static float K_0, K_1;	
	static float PP[2][2] = { { 1, 0 },{ 0, 1 } };

	angle += (gyro - Q_bias) * dt; 
	PP[0][0] = PP[0][0] + Q_angle - (PP[0][1] - PP[1][0])*dt;
	PP[0][1] = PP[0][1] - PP[1][1]*dt;
	PP[1][0] = PP[1][0] - PP[1][1]*dt;
	PP[1][1] = PP[1][0] + Q_gyro;
	K_0 = PP[0][0] / (PP[0][0] + R_measure);
	K_1 = PP[1][0] / (PP[0][0] + R_measure);
	angle = angle + K_0 * (acc - angle);
	Q_bias = Q_bias + K_1 * (acc - angle);
	PP[0][0] = PP[0][0] - K_0 * PP[0][0];
	PP[0][1] = PP[0][1] - K_0 * PP[0][1];
	PP[1][0] = PP[1][0] - K_1 * PP[0][0];
	PP[1][1] = PP[1][1] - K_1 * PP[0][1];
	
	return angle;
}
