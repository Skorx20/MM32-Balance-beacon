#ifndef _KEY_h
#define _KEY_h

#include "common.h"
#include "headfile.h"

#define key_up    1 
#define key_down  2 
#define key_left  3
#define key_right 4 
#define key_mid   5 

extern uint8 mode_flag;

void  key_init(void);
uint8 key_scan(void);
void oled_meun(void);
void oled_modify(void);
void modify_erect(void);
void modify_speed(void);
void modify_turn(void);
void modify_angspeed(void);
void modify_run(void);
void oled_state(void);
void oled_image(void);
void oled_motor(void);
void oled_run(void);

#endif
