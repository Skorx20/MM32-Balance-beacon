#ifndef _BLUETEETH_h
#define _BLUETEETH_h

#include "common.h"
#include "headfile.h"

extern uint8 data_buff[256];

void bt_send_int(char *str, uint8 num, uint8 digit);
void bt_send_double(char *str, double num, uint8 digit);

#endif
