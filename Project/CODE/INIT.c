#include "INIT.h"

#define SECTION_INDEX		FLASH_SECTION_127										// 最后一个扇区
#define PAGE_INDEX			FLASH_PAGE_3											// 最后一个页
#define DATA_SIZE			1024/sizeof(uint32)										// 32bit数据存储 缓冲就是1024/4大小
	
uint16 temp_data;
uint32 data_buffer[DATA_SIZE];
uint32 set_buffer[DATA_SIZE]={1,600,20,0,500,0,50,200,1,0,120,0,40,578,50,1,30,40,60};//{1,800,20,0,600,0,60,200,1,0,125,0,40,2167,50,1}
uint32 flash_flag=1;
uint8 *data_point = (uint8 *)data_buffer;

void system_init(void)
{
	board_init(true);		// debug初始化
	key_init();					// 按键初始化
	beep_init();
	oled_init();				// OLED初始化
	oled_p6x8str(0, 0, "Init Start");
	
	oled_p6x8str(0, 1, "Init Motor");
	motor_init();				// 电机初始化
	
	oled_p6x8str(0, 2, "Init Encoder");
	encoder_init();			// 编码器初始化
	
	oled_p6x8str(0, 3, "Init MPU");
	icm20602_init();		//陀螺仪初始化

	oled_p6x8str(0, 4, "Init Mt9v");
	mt9v03x_init();			// 摄像头初始化
	
	oled_p6x8str(0, 5, "Init PID");
	flash_read();	
	pid_init();					// PID参数初始化
	
	oled_p6x8str(0, 6, "Init Inter");
	tim_interrupt_init_ms(TIM_6,2,2);
	tim_interrupt_init_ms(TIM_7,5,3);	
	
	uart_init(UART_3,115200,UART3_TX_D08,UART3_RX_D09); 	//	蓝牙初始化

	oled_p6x8str(0, 7, "Init Success");
	systick_delay_ms(300);
	
	angle_deviation = 0;
	mpudata_turn();
	angle_deviation = 10-angle_now;
	
	oled_fill(0);
}

void flash_read(void)
{
	if(flash_check(SECTION_INDEX, PAGE_INDEX))										// 检查Flash是否有数据
	{
		flash_page_read(SECTION_INDEX, PAGE_INDEX, data_buffer, DATA_SIZE);			// 读出来已有的数据
	}
	else
	{
		flash_erase_page(SECTION_INDEX, PAGE_INDEX);								// 擦除页
		flash_page_program(SECTION_INDEX, PAGE_INDEX, set_buffer, DATA_SIZE);		// 写入预设数据
		flash_page_read(SECTION_INDEX, PAGE_INDEX, data_buffer, DATA_SIZE);			// 读出来
	}
	
	if(data_buffer[0]==0)
	{
		flash_erase_page(SECTION_INDEX, PAGE_INDEX);								// 擦除页
		flash_page_program(SECTION_INDEX, PAGE_INDEX, set_buffer, DATA_SIZE);		// 写入预设数据
		flash_page_read(SECTION_INDEX, PAGE_INDEX, data_buffer, DATA_SIZE);			// 读出来
	}
	else
	{
		flash_page_read(SECTION_INDEX, PAGE_INDEX, data_buffer, DATA_SIZE);			// 读出来已有的数据
	}
	
	flash_flag=data_buffer[0];
	pid_angspeed.kp=data_buffer[1];
	pid_angspeed.ki=data_buffer[2];
	pid_angspeed.kd=data_buffer[3];
	pid_erect.kp=data_buffer[4];
	pid_erect.ki=data_buffer[5];
	pid_erect.kd=data_buffer[6];
	pid_speed.kp=data_buffer[7];
	pid_speed.ki=data_buffer[8];
	pid_speed.kd=data_buffer[9];
	pid_turn.kp=data_buffer[10];
	pid_turn.ki=data_buffer[11];
	pid_turn.kd=data_buffer[12];
	expect_angle=data_buffer[13]/100.0;
	expect_angle=(-1)*expect_angle;
	threshold_def=data_buffer[14];
	speed_flag=data_buffer[15];
	down_far_point=data_buffer[16];
	down_near_point=data_buffer[17];
	cut_point=data_buffer[18];
}

void flash_write(void)
{
	data_buffer[0]=flash_flag;
	data_buffer[1]=pid_angspeed.kp;
	data_buffer[2]=pid_angspeed.ki;
	data_buffer[3]=pid_angspeed.kd;
	data_buffer[4]=pid_erect.kp;
	data_buffer[5]=pid_erect.ki;
	data_buffer[6]=pid_erect.kd;
	data_buffer[7]=pid_speed.kp;
	data_buffer[8]=pid_speed.ki;
	data_buffer[9]=pid_speed.kd;
	data_buffer[10]=pid_turn.kp;
	data_buffer[11]=pid_turn.ki;
	data_buffer[12]=pid_turn.kd;
	data_buffer[13]=(-1)*expect_angle*100;
	data_buffer[14]=threshold_def;
	data_buffer[15]=speed_flag;	
	data_buffer[16]=down_far_point;
	data_buffer[17]=down_near_point;
	data_buffer[18]=cut_point;
	
	flash_erase_page(SECTION_INDEX, PAGE_INDEX);								// 擦除页
	flash_page_program(SECTION_INDEX, PAGE_INDEX, data_buffer, DATA_SIZE);		// 写入缓冲数据
}
