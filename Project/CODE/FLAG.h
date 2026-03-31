#ifndef _FLAG_h
#define _FLAG_h

#include "common.h"
#include "headfile.h"

extern uint8 mode_flag;	//	运动模式	0调试	1发车
extern uint8 speed_flag;

extern uint8 filter_flag;	//	滤波选择	0膨胀	1腐蚀

extern uint8 find_flag;	//	有灯标志	0无灯	1有灯

extern uint8 cut_point;

extern uint8 down_far_point;
extern uint8 down_near_point;								
extern uint8 cut_point;

void run_car(void);

#endif
