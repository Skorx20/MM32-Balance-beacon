#include "BEEP.h"

void beep_init(void)
{
	gpio_init(F15,GPO,GPIO_LOW,GPO_PUSH_PULL);	
}

void beep_ring(void)
{
	static uint8 flag=0;
	static uint8 cut_time=2,find_time=2;
	
	if(find_flag)
	{
		if(y_coor < cut_point)
		{
			if(find_time>0)
			{
				flag=1-flag;
				find_time--;
			}
			else	flag=0;
		}
		else
		{
			if(cut_time>0)
			{
				flag=1-flag;
				cut_time--;
			}
			else	flag=0;
		}
	}
	else
	{
		flag=0;
		find_time=2;
		cut_time=2;
	}
	gpio_set(F15,flag);
}
