#ifndef _FUNCTION_h
#define _FUNCTION_h

#include "common.h"
#include "headfile.h"

double LPF_lst(double olddata, double newdata, float lpf_factor);

void Limit_data(double *value, double limit);

uint8 Sort_data(uint8 data0, uint8 data1, uint8 data2);

uint8 Median_filter(uint8 channal, uint8 data_in);

void Smooth_output(int16 *data, int16 expect, uint8 change);

#endif
