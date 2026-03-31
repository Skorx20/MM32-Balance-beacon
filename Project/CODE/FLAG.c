#include "FLAG.h"

uint8 mode_flag;	
uint8 speed_flag;

uint8 filter_flag=1;	

uint8 find_flag;	

uint8 down_far_point = 30;
uint8 down_near_point = 40;								

uint8	cut_point = 60;
										
void run_car(void)
{
	if(speed_flag==1)
	{
		//	直冲左转 cut58
		if(find_flag)												//	找到灯
		{
			if(y_coor < down_far_point)				//	正常
			{
				Smooth_output(&expect_speed, 1100, 10);
				expect_turn = x_coor-65;
			}
			else if(y_coor < down_near_point)	//	远处减速点
			{
				Smooth_output(&expect_speed, 1100, 10);
				expect_turn = x_coor-60;
			}
			else if(y_coor < cut_point)				//	近处减速点
			{
				Smooth_output(&expect_speed, 1100, 10);
				expect_turn = x_coor-60;
			}
			else															//	切灯点
			{
				Smooth_output(&expect_speed, 1100, 10);
				expect_turn= -120;
			}
		}
		else																//	丢灯
		{
			Smooth_output(&expect_speed, 1100, 10);
			expect_turn = -100;
		}
	}
	
	//	低速左转	cut59
	else if(speed_flag==2)
	{
		if(find_flag)												//	找到灯
		{
			if(y_coor < down_far_point)				//	正常
			{
				Smooth_output(&expect_speed, 1300, 20);
				expect_turn = x_coor-64;
			}
			else if(y_coor < down_near_point)	//	远处减速点
			{
				Smooth_output(&expect_speed, 1200, 20);
				expect_turn = x_coor-60;
			}
			else if(y_coor < cut_point)				//	近处减速点
			{
				Smooth_output(&expect_speed, 1150, 25);
				expect_turn = x_coor-55;
			}
			else															//	切灯点
			{
				Smooth_output(&expect_speed, 1150, 25);
				expect_turn= -110;
			}
		}
		else																//	丢灯
		{
			Smooth_output(&expect_speed, 1200, 10);
			expect_turn = -100;
		}
	}
	
	//	中速左转	cut60
	else if(speed_flag==3)
	{
		if(find_flag)												//	找到灯
		{
			if(y_coor < down_far_point)				//	正常
			{
				Smooth_output(&expect_speed, 1500, 20);
				expect_turn = x_coor-60;
			}
			else if(y_coor < down_near_point)	//	远处减速点
			{
				Smooth_output(&expect_speed, 1300, 20);
				expect_turn = x_coor-38;
			}
			else if(y_coor < cut_point)				//	近处减速点
			{
				Smooth_output(&expect_speed, 1250, 50);
				expect_turn = x_coor-58;
			}
			else															//	切灯点
			{
				Smooth_output(&expect_speed, 1200, 25);
				expect_turn= -125;
			}
		}
		else																//	丢灯
		{
			Smooth_output(&expect_speed, 1300, 10);
			expect_turn = -115;
		}
	}
	
	//	高速左转	cnt60
	else if(speed_flag==4)
	{
		if(find_flag)												//	找到灯
		{
			if(y_coor < down_far_point)				//	正常
			{
				Smooth_output(&expect_speed, 1600, 25);
				expect_turn = x_coor-60;
			}
			else if(y_coor < down_near_point)	//	远处减速点
			{
				Smooth_output(&expect_speed, 1300, 50);
				expect_turn = x_coor-45;
			}
			else if(y_coor < cut_point)				//	近处减速点
			{
				Smooth_output(&expect_speed, 1250, 25);
				expect_turn = x_coor-55;
			}
			else															//	切灯点
			{
				Smooth_output(&expect_speed, 1200, 25);
				expect_turn= -125;
			}
		}
		else																//	丢灯
		{
			Smooth_output(&expect_speed, 1300, 25);
			expect_turn = -115;
		}
	}

	//	直冲右转	cut58
	else if(speed_flag==5)
	{
		if(find_flag)												//	找到灯
		{
			if(y_coor < down_far_point)				//	正常
			{
				Smooth_output(&expect_speed, 1100, 10);
				expect_turn = x_coor-65;
			}
			else if(y_coor < down_near_point)	//	远处减速点
			{
				Smooth_output(&expect_speed, 1100, 10);
				expect_turn = x_coor-70;
			}
			else if(y_coor < cut_point)				//	近处减速点
			{
				Smooth_output(&expect_speed, 1100, 10);
				expect_turn = x_coor-70;
			}
			else															//	切灯点
			{
				Smooth_output(&expect_speed, 1100, 10);
				expect_turn= 120;
			}
		}
		else																//	丢灯
		{
			Smooth_output(&expect_speed, 1100, 10);
			expect_turn = 100;
		}
	}
	
	//	低速右转	cut59
	else if(speed_flag==6)
	{
		if(find_flag)												//	找到灯
		{
			if(y_coor < down_far_point)				//	正常
			{
				Smooth_output(&expect_speed, 1300, 20);
				expect_turn = x_coor-64;
			}
			else if(y_coor < down_near_point)	//	远处减速点
			{
				Smooth_output(&expect_speed, 1200, 20);
				expect_turn = x_coor-65;
			}
			else if(y_coor < cut_point)				//	近处减速点
			{
				Smooth_output(&expect_speed, 1150, 25);
				expect_turn = x_coor-66;
			}
			else															//	切灯点
			{
				Smooth_output(&expect_speed, 1150, 25);
				expect_turn= 110;
			}
		}
		else																//	丢灯
		{
			Smooth_output(&expect_speed, 1200, 10);
			expect_turn = 100;
		}
	}
	
	//	中速右转	cut60
	else if(speed_flag==7)
	{
		if(find_flag)												//	找到灯
		{
			if(y_coor < down_far_point)				//	正常
			{
				Smooth_output(&expect_speed, 1500, 20);
				expect_turn = x_coor-60;
			}
			else if(y_coor < down_near_point)	//	远处减速点
			{
				Smooth_output(&expect_speed, 1300, 20);
				expect_turn = x_coor-40;
			}
			else if(y_coor < cut_point)				//	近处减速点
			{
				Smooth_output(&expect_speed, 1250, 50);
				expect_turn = x_coor-85;
			}
			else															//	切灯点
			{
				Smooth_output(&expect_speed, 1200, 25);
				expect_turn= 150;
			}
		}
		else																//	丢灯
		{
			Smooth_output(&expect_speed, 1300, 10);
			expect_turn = 130;
		}
	}
	
	//	高速右转
	else if(speed_flag==8)
	{
		if(find_flag)												//	找到灯
		{
			if(y_coor < down_far_point)				//	正常
			{
				Smooth_output(&expect_speed, 1600, 20);
				expect_turn = x_coor-70;
			}
			else if(y_coor < down_near_point)	//	远处减速点
			{
				Smooth_output(&expect_speed, 1300, 20);
				expect_turn = x_coor-85;
			}
			else if(y_coor < cut_point)				//	近处减速点
			{
				Smooth_output(&expect_speed, 1250, 25);
				expect_turn = x_coor-80;
			}
			else															//	切灯点
			{
				Smooth_output(&expect_speed, 1200, 25);
				expect_turn= 120;
			}
		}
		else																//	丢灯
		{
			Smooth_output(&expect_speed, 1300, 10);
			expect_turn = 100;
		}
	}
}
