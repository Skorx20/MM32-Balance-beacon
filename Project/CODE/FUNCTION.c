#include "FUNCTION.h"

//	一阶低通互补滤波
double LPF_lst(double olddata, double newdata, float lpf_factor)
{
	return olddata * (1 - lpf_factor) + newdata * lpf_factor;
}

//	数据限幅
void Limit_data(double *value, double limit)
{
	if(limit > 0)
	{
		if(*value > limit)		*value = limit;
		if(*value < -limit)		*value = -limit;
	}
	else if(limit < 0)
	{
		if(*value > -limit)		*value = -limit;
		if(*value < limit)		*value = limit;
	}
}

//	数据排序
uint8 Sort_data(uint8 data0, uint8 data1, uint8 data2)
{
	uint8 temp=0;
	if(data0 > data1)
	{
		temp=data0;
		data0=data1;
		data1=temp;
	}
	if(data0 > data2)
	{
		temp=data0;
		data0=data2;
		data2=temp;
	}
	if(data1 > data2)
	{
		temp=data1;
		data1=data2;
		data2=temp;
	}
	return data1;
}

//	中位数滤波
uint8 Median_filter(uint8 channal, uint8 data_in)
{
	static uint8 Data[2][3]={0};
	uint8 temp;
	Data[channal][0] = Data[channal][1];
	Data[channal][1] = Data[channal][2];
	Data[channal][2] = data_in;
	temp = Sort_data(Data[channal][0],Data[channal][1],Data[channal][2]);
	
	return temp;
}

//	平滑输出
void Smooth_output(int16 *data, int16 expect, uint8 change)
{
	if(*data < expect)
		*data += change;
	else if(*data > expect)
		*data -= change;
}
