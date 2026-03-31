#ifndef _ENCODER_h
#define _ENCODER_h

#include "common.h"
#include "headfile.h"

#define encoder_R_TIM TIM_3
#define encoder_L_TIM TIM_4
#define encoder_R_A TIM_3_ENC2_B05
#define encoder_R_B TIM_3_ENC1_B04
#define encoder_L_A TIM_4_ENC1_B06
#define encoder_L_B TIM_4_ENC2_B07

void encoder_init(void);
int16 encoder_read(TIM_enum tim);
int16 get_encoder(void);

#endif
