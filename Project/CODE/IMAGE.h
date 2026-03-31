#ifndef _IMAGE_h
#define _IMAGE_h

#include "common.h"
#include "headfile.h"

#define width 128
#define height 64

extern uint8 dis_img[height][width];	// 显示图像（处理后）

extern uint8 twinkle_img[height][width];	//	闪烁处理后图像

extern uint8 x_coor, y_coor;

extern int16 light;

extern uint8 threshold_def;

uint8 otus_threshold(uint8 *image);
void  img_get(void);
void  img_filter(void);
void  img_findLR(void);
void  img_findXY(void);
void 	img_find(void);
void  img_deal(void);
void	img_twinkle(void);

#endif
