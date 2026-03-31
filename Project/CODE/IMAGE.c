#include "IMAGE.h"

#define GrayScale 256   //frame灰度级

// 灯各阶段图像
uint8 binary_img[height][width];  // 二值化后的图像
uint8 erodila_img[height][width]; // 腐蚀后的图像
uint8 dis_img[height][width];     // 显示图像（处理后）
uint8 twinkle_img[height][width];	// 闪烁处理后图像
uint8 last_img[height][width];		// 上一帧图像

uint8 x_coor, y_coor;

uint8 ostu_flag=0;

uint8 ostu_min = 100;

uint8 threshold_def;

uint8 threshold;

int16 light;

int pixel[256]={0}; 
 
uint8 otus_threshold(uint8 *image)
{
	int threshold1=0;
	int32_t sum_gray =0 ;
	int32_t sum_pix_num = 0;
	int32_t pl_pix_num = 0;
	int32_t p2_pix_mum = 0;
	int32_t p1_sum_gray = 0;
	float m1 = 0;
	float m2 = 0;
	float V = 0;
	float variance = 0;
	int i,j,k=0;
	
	for(i = 0;i<256;i++)
		pixel[i] = 0;
	
	//统计每个灰度级中像素的个数   
    for(i = 0; i < height; i++)   
        for(j = 0;j < width;j++) 
            pixel[(int)image[i * width + j]]++;  

		for(k=0;k<GrayScale;k++)
		{
			sum_gray += k * pixel[k];//灰度直方图质量矩
			sum_pix_num += pixel[k];//总像素个数
		}	
		
		for(k=0;k<GrayScale-1;k++)
		{
			pl_pix_num += pixel[k];//第一部分像素个数
			p2_pix_mum = sum_pix_num - pl_pix_num;//第二部分像素个数
			p1_sum_gray += k * pixel[k];   //第一部分质量矩
			m1 = (float)p1_sum_gray / pl_pix_num;//第一部分灰度均值
			m2 = (float)(sum_gray-p1_sum_gray) / p2_pix_mum;//第二部分灰度均值
			
			V = pl_pix_num * p2_pix_mum * (m1-m2) * (m1-m2);
			
			if(V > variance)//将类间方差较大时的灰度值作为阈值
			{
				variance = V;
				threshold1 = k;
			}
		}
		return threshold1;
}


//	图像获取
void img_get(void)
{
	if(mt9v03x_finish_flag)
  {
    mt9v03x_finish_flag = 0;
		
		if (ostu_flag == 1)
    {
        threshold = otus_threshold(mt9v03x_image[0]);
        if (threshold < ostu_min) 
          threshold = ostu_min;
    }
    else
      threshold = threshold_def;   
		
		uint8 i=0,j=0;
    for(i=0;i<height;i++)
    {
      for(j=0;j<width;j++)
      {
				if(filter_flag==0)
				{
				  if(*(*(mt9v03x_image+i)+j) > threshold) *(*(dis_img+i)+j)=1;
					else *(*(dis_img+i)+j) = 0;
				}
				else
				{
					if(*(*(mt9v03x_image+i)+j) > threshold) *(*(binary_img+i)+j)=1;
					else *(*(binary_img+i)+j) = 0;
				}
      }
    }
	}
  return;
}
 

//	图像中值滤波
void img_filter(void) 
{
   uint8 i=0,j=0;
   uint8 sum;
    for (i=0; i<height; i++)
    {
        for (j=0; j<width; j++)
        {
            if (i!=0 && i!=height-1 && j!=0 && j!=width-1)
            {
                sum = *(*(binary_img+i-1)+j-1) + *(*(binary_img+i-1)+j) + *(*(binary_img+i-1)+j+1)
                    + *(*(binary_img+i)+j-1)   + *(*(binary_img+i)+j)   + *(*(binary_img+i)+j+1)
                    + *(*(binary_img+i+1)+j-1) + *(*(binary_img+i+1)+j) + *(*(binary_img+i+1)+j+1);
                if (sum >= 1) *(*(dis_img+i)+j) = 1;
                else          *(*(dis_img+i)+j) = 0;
            }
            else    *(*(dis_img+i)+j) = *(*(binary_img+i)+j);
        }
    }
    return;
}


//	图像腐蚀膨胀处理
void img_erodila(void) 
{
  uint8 i=0,j=0;

	for (i=0; i<height; i++)
	{
		for (j=0; j<width; j++)
		{
			if (i!=0 && i!=height-1 && j!=0 && j!=width-1)
			{
				//	腐蚀
				if(filter_flag==2)
				{
					if(*(*(binary_img+i)+j-1)==0||*(*(binary_img+i-1)+j)==0||*(*(binary_img+i)+j+1)==0||*(*(binary_img+i+1)+j)==0||*(*(binary_img+i)+j)==0)
								*(*(dis_img+i)+j) = 0;
					else  *(*(dis_img+i)+j) = 1;
				}
				//	膨胀
				else if(filter_flag==1)
				{
					if(*(*(binary_img+i)+j-1)==1||*(*(binary_img+i-1)+j)==1||*(*(binary_img+i)+j+1)==1||*(*(binary_img+i+1)+j)==1||*(*(binary_img+i)+j)==1)
//	                if(erodila_img[i][col-1]==1||erodila_img[i-1][col]==1||erodila_img[i][col+1]==1||erodila_img[i+1][col]==1||erodila_img[i][col]==1)
								*(*(dis_img+i)+j) = 1;
					else  *(*(dis_img+i)+j) = 0;
				}
			}
			else	*(*(dis_img+i)+j) = *(*(binary_img+i)+j);
		}
	}
  return;
}

void img_find(void){
	uint8 i, j;
	uint8 left,up,right,down;
	uint8 area = 0;
	uint8 img_flag = 0;
	uint8 line=0, last_line=0;
	uint8 line_sun;
	static uint8 count=0;
	static uint8 x_last,y_last;
	
	for(i = height-1;i>0;i--)
	{
		line = 0;line_sun=0;
		for(j = 0; j<width; j++)
		{
			if(*(*(dis_img+i)+j) ==1 && img_flag == 0)  
			{
				img_flag = 1;
				left = j;
				down = i;
			}
			if(*(*(dis_img+i)+j) == 1)
			{
				area++;
				line_sun++;
				up = i;
				right = j;
				line++;
			}
		}
		
		if(area > 0)
		{
//			row_dev = down-up;
//			col_dev = right-left;
//			
//			if(row_dev > 0 && col_dev > 0 && row_dev > 3*col_dev)
//			{
//				area=0;
//				break;
//			}
//			
//			if(line_sun > 30)
//			{
//				area=0;
//				break;
//			}
			
			if(last_line > 0 && line == 0)	break;
			last_line = line;
		}	
	}
	
	if(area > 30)
	{
		if((up+down)/2 < 20)
			area=0;
	}
	
	if(area > 0)	//	找到灯
	{		
		find_flag = 1;
		count = 0;
		x_coor = Median_filter(0, (left+right)/2);
		y_coor = Median_filter(1, (up+down)/2);
		x_last = x_coor;
		y_last = y_coor;
	}
	else	//	没找到灯
	{
		count++;
		if(count == 3)
		{
			find_flag = 0;
			count = 0;
			x_last = 0;						
			y_last = 0;
			Median_filter(0, 0);	
			Median_filter(1, 0);
		}
		
		x_coor = x_last;
		y_coor = y_last;
	}
		
	return;
}


void img_deal(void)
{
		img_get();
		if(filter_flag)	img_erodila();
		img_find();
}

// 处理闪烁图像
void img_twinkle(void)
{
  uint8 i,j;

  for(i=0;i<height;i++)
  {
    for(j=0;j<width;j++)
    {
      twinkle_img[i][j]=last_img[i][j] ^ dis_img[i][j];               
      last_img[i][j]=dis_img[i][j];
    }
  }
}
