#include "KEY.h"
#include "headfile.h"

#define key_com   0  
#define key_up    1  // PG2
#define key_down  2  // PG4
#define key_left  3  // PG3
#define key_right 4  // PG6
#define key_mid   5  // PG5
#define key_flag  6  // PG5

int8 select_num=0;  // 选择功能记录数字

uint8 page_flag=0;


// 按键初始化
void key_init(void)
{
	mode_flag=0;
  gpio_init(G2,GPI,GPIO_HIGH,GPI_PULL_UP);
  gpio_init(G3,GPI,GPIO_HIGH,GPI_PULL_UP);
  gpio_init(G4,GPI,GPIO_HIGH,GPI_PULL_UP);
  gpio_init(G5,GPI,GPIO_HIGH,GPI_PULL_UP);
  gpio_init(G6,GPI,GPIO_HIGH,GPI_PULL_UP);
	gpio_init(G7,GPI,GPIO_HIGH,GPI_PULL_UP);
}

// 按键选择判断
uint8 key_scan(void)
{
  if(gpio_get(G2) == 0)
  {
    systick_delay_ms(10);
    while (gpio_get(G2) == 0);
    return key_down;
  }
  else if(gpio_get(G3) == 0)
  {
    systick_delay_ms(10);
    while (gpio_get(G3) == 0);
    return key_right;
  }
  else if(gpio_get(G4) == 0)
  {
    systick_delay_ms(10);
    while (gpio_get(G4) == 0);
    return key_up;
  }
  else if(gpio_get(G5) == 0)
  {
    systick_delay_ms(10);
    while (gpio_get(G5) == 0);
    return key_mid;
  }
  else if(gpio_get(G6) == 0)
  {
    systick_delay_ms(10);
    while (gpio_get(G6) == 0);
    return key_left;
  }
	 else if(gpio_get(G7) == 0)
  {
    systick_delay_ms(10);
    while (gpio_get(G7) == 0);
    return key_flag;
  }
  else return 0;
}


// 主菜单
void oled_meun(void)
{
	oled_fill(0x00);
	while(1)
	{
		oled_str(0,0,"Modify"); 
		oled_str(0,2,"State");
		oled_str(0,4,"Image");
		oled_str(0,6,"Run");
		oled_str(120,select_num,"Y"); 
		
		switch(key_scan())
		{
			case key_up:
				oled_fill(0x00);
				select_num-=2;
				if(select_num<0)	select_num=6;
				break;
			
			case key_down:
				oled_fill(0x00);
				select_num+=2;
				if(select_num>6)	select_num=0;
				break;
			
			case key_mid:
				oled_fill(0x00);
				switch(select_num)
				{
					case 0:
						select_num=0;
						oled_modify();
						break;
					case 2:
						select_num=0;
						oled_state();
					  select_num=2;
						break;
					case 4:
						oled_image();
						select_num=4;
						break;
				  case 6:
						oled_run();
						select_num=6;
						break;
				}
				oled_fill(0x00);
				break;
				
				case key_flag:
					  mode_flag=1-mode_flag;
				break;
		}
	}
}


// 修改界面
void oled_modify(void)
{
  while(1)
  {
		if(page_flag==0)
		{
			oled_str(0,0,"Save");
			oled_str(0,2,"Angspeed");   
			oled_str(0,4,"Erect");
			oled_str(0,6,"Speed");
			oled_str(120,select_num,"Y");  
		
			switch(key_scan())  
			{
				case key_up:       
					select_num -= 2;
					if (select_num<0) 
					{
						select_num=0;
						page_flag=!page_flag;
					}  
					oled_fill(0x00);
					break;
				
				case key_down:   
					select_num += 2;
					if (select_num>6) 
					{
						select_num=0;  
					}
					oled_fill(0x00);
					break;
					
				case key_mid:
					oled_fill(0x00);
					switch(select_num)  
					{
						case 0:
							flash_write();		
							return;
						case 2:
							select_num=2;
							modify_angspeed();
							select_num=2;
							break;
						case 4:
							select_num=2;
							modify_erect();
							select_num=4;
							break;
						case 6:
							select_num=2;
							modify_speed();
							select_num=6;
							break;
					}
					oled_fill(0x00);
					break;
					
				case key_left:
					if(select_num==0)	return;
					break;
					
				case key_right:
					if(select_num==0)	return;	
					break;
				
				case key_flag:
					  mode_flag=1-mode_flag;
				break;
			}
		}
		//	第二面
		else
		{
			oled_str(0,0,"Turn");
			
			oled_str(0,2,"Down far");
			oled_uint16(80,2,down_far_point);
			
			oled_str(0,4,"Down near");
			oled_uint16(80,4,down_near_point);
			
			oled_str(0,6,"Cut");
			oled_uint16(80,6,cut_point);
			
			oled_str(120,select_num,"Y");  
			
			switch(key_scan())  
			{
				
				case key_up:       
					select_num -= 2;
					if (select_num<0) 
					{
						select_num=0;
						page_flag=!page_flag;
					}  
					oled_fill(0x00);
					break;
				
				case key_down:   
					select_num += 2;
					if (select_num>6) 
					{
						select_num=0;  
					}
					oled_fill(0x00);
					break;
				
				case key_mid:
					if(select_num==0)
					{
						oled_fill(0x00);
						select_num=2;
						modify_turn();
						select_num=0;
						oled_fill(0x00);
					}
					else
					{
						flash_write();
						return;
					}
					break;
					
				case key_left:
					if(select_num==2)	down_far_point-=1;
					else if(select_num==4)	down_near_point-=1;
					else if(select_num==6)	cut_point-=1;
					break;
					
				case key_right:
					if(select_num==2)	down_far_point+=1;
					else if(select_num==4)	down_near_point+=1;
					else if(select_num==6)	cut_point+=1;
					break;
					
				case key_flag:
				  mode_flag=1-mode_flag;
					break;
			}
		}
	}
}

// 角速度环
void modify_angspeed(void)
{
	while(1)
  {
    oled_str(0,0,"Angspeed");   
    oled_str(0,2,"P:");
		oled_uint16(16, 2, pid_angspeed.kp);
    oled_str(0,4,"I:");
		oled_uint16(16, 4, pid_angspeed.ki);
    oled_str(0,6,"D:");
		oled_uint16(16, 6, pid_angspeed.kd);
    oled_str(120,select_num,"Y");  
  
    switch(key_scan())  
    {
      case key_up:		
        select_num -= 2;
        if (select_num<2) select_num=6;  
			  oled_fill(0x00);
        break;
      
      case key_down:		
        select_num += 2;
        if (select_num>6) select_num=2;  
			  oled_fill(0x00);
        break;

			case key_left:		
				switch(select_num)
				{
					case 2:
						pid_angspeed.kp-=50;// 修改P值
						break;
					
					case 4:
						pid_angspeed.ki-=1;
						// 修改I值
						break;
					
					case 6:

						break;
				}
				break;
			//	右键	
			case key_right:
				switch(select_num)
				{
					case 2:
						pid_angspeed.kp+=50;// 修改P值
						break;
					
					case 4:
						pid_angspeed.ki+=1;
						// 修改I值
						break;
					
					case 6:
						break;
				}
				break;
      // 退出  
				
				case key_flag:
					  mode_flag=1-mode_flag;
						break;
							
      case key_mid:
				pid_init();
				//flash_write();
				return;
    }
  }
}


// 直立环
void modify_erect(void)
{
	while(1)
  {
    oled_str(0,0,"Erect");   
    oled_str(0,2,"P:");
		oled_uint16(16, 2, pid_erect.kp);
    oled_str(0,4,"I:");
		oled_uint16(16, 4, pid_erect.ki);
    oled_str(0,6,"D:");
		oled_uint16(16, 6, pid_erect.kd);
    oled_str(120,select_num,"Y");  
  
    switch(key_scan())  
    {
      case key_up:		
        select_num -= 2;
        if (select_num<2) select_num=6;  
			  oled_fill(0x00);
        break;
      
      case key_down:		
        select_num += 2;
        if (select_num>6) select_num=2;  
			  oled_fill(0x00);
        break;
			//	左键
			case key_left:
				switch(select_num)
				{
					case 2:
						pid_erect.kp-=10;// 修改P值
						break;
					
					case 4:
						// 修改I值
						break;
					
					case 6:
						pid_erect.kd-=1;// 修改D值
						break;
				}
				break;
			// 右键	
			case key_right:
				switch(select_num)
				{
					case 2:
						pid_erect.kp+=10;// 修改P值
						break;
					
					case 4:
						// 修改I值
						break;
					
					case 6:
						pid_erect.kd+=1;// 修改D值
						break;
				}
				break;

			case key_flag:
					 mode_flag=1-mode_flag;
					break;
								
      case key_mid:
				pid_init();
				//flash_write();
				return;
    }
  }
}


// 速度环
void modify_speed(void)
{
	while(1)
  {
    oled_str(0,0,"Speed");   
    oled_str(0,2,"P:");
		oled_uint16(16, 2, pid_speed.kp);
    oled_str(0,4,"I:");
		oled_uint16(16, 4, pid_speed.ki);
    oled_str(0,6,"D:");
		oled_uint16(16, 6, pid_speed.kd);
    oled_str(120,select_num,"Y");  
  
    switch(key_scan())  
    {
      case key_up:		
        select_num -= 2;
        if (select_num<2) select_num=6;  
			  oled_fill(0x00);
        break;
      
      case key_down:	
        select_num += 2;
        if (select_num>6) select_num=2;  
			  oled_fill(0x00);
        break;
			//	左键
			case key_left:
				switch(select_num)
				{
					case 2:
						pid_speed.kp-=10;// 修改P值
						break;
					
					case 4:
						pid_speed.ki-=1;
						break;
				}
				break;
			//	右键	
			case key_right:
				switch(select_num)
				{
					case 2:
						pid_speed.kp+=10;// 修改P值
						break;
					
					case 4:
						pid_speed.ki+=1;
						break;
				}
				break;
				
			case key_flag:
					 mode_flag=1-mode_flag;
					break;
			
      case key_mid:
				pid_init();
				return;
    }
  }
}


// 方向环
void modify_turn(void)
{
	while(1)
  {
    oled_str(0,0,"Turn");   
    oled_str(0,2,"P:");
		oled_uint16(16, 2, pid_turn.kp);
    oled_str(0,4,"I:");
		oled_uint16(16, 4, pid_turn.ki);
    oled_str(0,6,"D:");
		oled_uint16(16, 6, pid_turn.kd);
    oled_str(120,select_num,"Y");  
  
    switch(key_scan())  
    {
      case key_up:		
        select_num -= 2;
        if (select_num<2) select_num=6;  
			  oled_fill(0x00);
        break;
      
      case key_down:		
        select_num += 2;
        if (select_num>6) select_num=2;  
			  oled_fill(0x00);
        break;
			//	左键
			case key_left:
				switch(select_num)
				{
					case 2:
						pid_turn.kp-=1;// 修改P值
						break;
					
					case 4:
						// 修改I值
						break;
					
					case 6:
						pid_turn.kd-=1;// 修改D值
						break;
				}
				break;
			//	右键	
			case key_right:
				switch(select_num)
				{
					case 2:
						pid_turn.kp+=1;// 修改P值
						break;
					
					case 4:
						// 修改I值
						break;
					
					case 6:
						pid_turn.kd+=1;// 修改D值
						break;
				}
				break;
				
			case key_flag:
					 mode_flag=1-mode_flag;
					break;
			
      case key_mid:
				pid_init();
				return;
    }
  }
}

// 状态页面
void oled_state(void)
{
	while(1)
	{
		img_deal();
		oled_float(0, 0, angle_now, 2, 2);
		oled_float(64, 0, expect_angle, 2, 2);
		
		oled_uint16(0, 2, threshold_def);
		
		oled_uint16(0,4,speed_flag);
		
		oled_printf_int32(16,6,x_coor,3);
		oled_printf_int32(48,6,y_coor,2);
		
		if(flash_flag==1)	oled_str(8,6,"1");
		else	oled_str(8,6,"0");
		
		oled_str(120,select_num,"Y"); 
		
		switch(key_scan())
		{
			case key_flag:
				mode_flag=1-mode_flag;
				break;
			
			case key_mid:
				oled_fill(0x00);
				flash_write();		
				return;
			
			case key_right:
				if(select_num==0)	expect_angle+=0.1;
				else if(select_num==2)	threshold_def+=1;
				else if(select_num==4)	speed_flag+=1;
				else if(select_num==6)	flash_flag=!flash_flag;
				break;
			
			case key_left:
				if(select_num==0)	expect_angle-=0.1;
				else if(select_num==2)	threshold_def-=1;
				else if(select_num==4)	speed_flag-=1;
				else if(select_num==6)	flash_flag=!flash_flag;
				break;
			
			case key_up:
				select_num -= 2;
				if(select_num<0)	select_num=6;
			  oled_fill(0x00);
				break;
			
			case key_down:
				select_num +=2;
				if(select_num>6)	select_num=0;
			  oled_fill(0x00);
				break;
				
		}
	}
}


// 图像页面
void oled_image(void)
{
	while(1){
		img_deal();
		oled_dis_bmp(64, 128, dis_img[0], threshold_def);
//		printf("abc=%f",angle_now);
		run_car();
		switch(key_scan())
		{
			case key_flag:
				mode_flag=1-mode_flag;
				break;
			
			case key_mid:
				return;
		}
	}
}

void oled_motor(void)
{
	nvic_interrput_disable();
	uint16 left_motor=2500,right_motor=2500;
	
	while(1)
	{
		oled_str(0,0,"Threshold:");
		oled_uint16(80, 0, threshold_def);
//		oled_str(0,2,"Light:");
//		oled_uint16(80, 2, light);
		
		oled_str(0,4,"Left :");
		oled_printf_int32(48, 4, left_motor, 4);
		oled_str(0,6,"Right:");
		oled_printf_int32(48, 6, right_motor, 4);
		
		oled_str(120,select_num,"Y");  
		
		motor_speed(-left_motor, -right_motor);
		
		switch(key_scan())
		{
			case key_up:
				select_num -=2;
				if(select_num<0)	select_num=6;
			  oled_fill(0x00);
				break;
			
			case key_down:
				select_num+=2;
				if(select_num>6)	select_num=0;
					oled_fill(0x00);
				break;
			
			case key_left:
				switch(select_num)
				{
					case 0:
						threshold_def-=1;
						break;
					
					case 2:
						light-=5;
						break;
					
					case 4:
						left_motor-=50;
						break;
					
					case 6:
						right_motor-=50;
						break;
				}
				break;

			case key_right:
				switch(select_num)
				{
					case 0:
						threshold_def+=1;
						break;
					
					case 2:
						light+=5;
						break;
					
					case 4:
						left_motor+=50;
						break;
					
					case 6:
						right_motor+=50;
						break;
				}
				break;
			
			case key_flag:
					 mode_flag=1-mode_flag;
					break;
			
			case key_mid:
				flash_write();
	 			nvic_interrput_enable();
				return;
		}
	}
}


void oled_run(void)
{
	mode_flag=1;
	while(1){
		img_deal();
		run_car();
		if(key_scan()==key_mid)
		{
			mode_flag=0;
			return;
		}
	}
}
