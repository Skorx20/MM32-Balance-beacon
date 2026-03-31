void run(int16 *forward, int16 *turn)
{
	int16 dir;
	static int16 last;
	
	if(searching(&dir)==Exist)	//	灯在视野内
	{
		if(down_flag==0)	//	未到减速点
			fb ++;
			fb = fb > speed_max? speed_max : fb;
		else if(down_flag==1)
			fb --;
			fb = fb < speed_min? speed_min : fb;
		
		if(cut_flag==0)	//	未到切灯点
		{
			if(dir==last)
			{
				if(dir==Left)
					lr --;
				else if(dir==Right)
					lr ++;
			}
			else
				lr =0;
			last=dir;
		}
		else if(cut_flag==1)
		{
			fb+=5;
			lr-=5;
		}
				
	}
	else	//	灯不在视野内
	{
		fb--;
		lr-=5;
	}
}


void run(int16 *forward,int16 *turn)
{
	int16 dir;
	static int16 down_flag,cut_flag,last;
	if(searching(&dir)==Exist) //灯在视野内
	{
		down_flag=0;
//		if(cut_flag==0) //未到减速点，切灯点
//		{
			*forward +=1;
			if(dir==last)
			{
				if(dir==Left)
					*turn -=1;
				else if(dir==Right)
					*turn +=1;
			}
			else
			{
				*turn =0;
			}
//		}
//		else
//		{
//				*turn-=1;
//		}
	}
	else //灯不在视野内
	{
		if(down_flag==0) //灭灯后
			down_flag=1;
		if(down_flag==1)
		{
			if(*forward>10)
				*forward -=1;
			else
				down_flag=0;
		}
		*turn -=1;
	}
}


int searching(int16 *dir)
{	
	if(x_coor==0 && y_coor==0)
		return None;
	else if(x_coor<62)
		*dir=Right;
	else if(x_coor>64)
		*dir=Left;
	else
		*dir=Forward;
	return Exist;
}


//	图像寻找边界
uint16 deviation[height];

void img_findLR(void)  
{
  uint8 i,j;
  unsigned char lside=width,rside=0;

  for(i=0; i<height; i++)
  {
    lside=width,rside=0;
    for(j=0; j<width-1; j++)
    {
      if(dis_img[i][j] && dis_img[i][j+1])            //同一行中连续两个像素点亮
      {
        if(lside==width) lside=j;             //定左边缘
        rside=j+1;                            //定右边缘
      }
    }
    if(lside < rside) 
			deviation[i]=(lside+rside)/2;    
    else           
			deviation[i]=0xff;
  }
  return;
}


//	图像寻找中心点
void img_findXY(void)
{
  int i=0,k=0,p=0,g=0,m=0,q=0;
  float Xx=0;
  
  for(i=0;i<height-1;i++)
  {
     if((deviation[i]!=0xff)&&(deviation[i+1]!=0xff))         //连续四个点表示确定为信标灯而不是噪点
     {
       if(g==0)
       {
         k=i;g=1;
       }
       if(m==0) p++;
     }
     else if(g==1) m=1;
  }
  for(q=0;q<p-1;q++) Xx+=deviation[k+q];
  x_coor = Xx/(p-1);
  y_coor =(k+(p>>1));                                       //右移一位相当于除以二 而运算速度更快
}