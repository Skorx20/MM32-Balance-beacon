#ifndef _INIT_h
#define _INIT_h

#include "common.h"
#include "headfile.h"

#define SECTION_INDEX		FLASH_SECTION_127										// 最后一个扇区
#define PAGE_INDEX			FLASH_PAGE_3											// 最后一个页
#define DATA_SIZE			1024/sizeof(uint32)										// 32bit数据存储 缓冲就是1024/4大小
	
extern uint32 data_buffer[DATA_SIZE];
extern uint32 flash_flag;

void system_init(void);
void flash_read(void);
void flash_write(void);

#endif
