#include "BLUETEETH.h"

uint8 data_buff[256];


//-------------------------------------------------------------------------------------------------------------------
//	brief			À¶ÑÀ·¢ËÍÕûÊı
//	param			str:·¢ËÍµÄÊı¾İÃû	num:·¢ËÍµÄÊıÖµ	digit:·¢ËÍÊıÖµµÄÎ»Êı
//	notes			¸ººÅÕ¼Ò»Î»
//	example		bt_send_int("x", x_coor, 3)
// 	author		Tren
//-------------------------------------------------------------------------------------------------------------------
void bt_send_int(char *str, uint8 num, uint8 digit)
{
	uint8 cnt=0;
	char text[digit];
	uint8 i = digit+1;
	
	while(*str)
		data_buff[cnt++]=*str++;
	
	data_buff[cnt++]=0x3D;
	
	sprintf(text,"%d",num);
	
	while(i--)
		data_buff[cnt++]=*(text+digit-i);
	
	data_buff[cnt++]=0x0A;
	
	uart_putbuff(UART_3,data_buff,cnt);
}

//-------------------------------------------------------------------------------------------------------------------
//	brief			À¶ÑÀ·¢ËÍ¸¡µãÊı
//	param			str:·¢ËÍµÄÊı¾İÃû	num:·¢ËÍµÄÊıÖµ	digit:·¢ËÍÊıÖµµÄÎ»Êı
//	notes			¸ººÅÕ¼Ò»Î»	Ğ¡Êıµã²»Õ¼Î»Êı
//	example		bt_send_double("angle", angle_now, 5);
// 	author		Tren
//-------------------------------------------------------------------------------------------------------------------ı
void bt_send_double(char *str, double num, uint8 digit)
{
	uint8 cnt=0;
	char text[digit];
	uint8 i = digit+1;
	
	while(*str)
		data_buff[cnt++]=*str++;
	
	data_buff[cnt++]=0x3D;
	
	sprintf(text,"%f",num);
	
	while(i--)
		data_buff[cnt++]=*(text+digit-i);
	
	data_buff[cnt++]=0x0A;
	
	uart_putbuff(UART_3,data_buff,cnt);
}
