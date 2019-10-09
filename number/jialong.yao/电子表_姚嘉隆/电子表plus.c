#include "reg51.h"
#define uchar unsigned char
#define uint unsigned int
void carry(void);
void display(void);
void wrinkle(void);
void KeyControl(uchar key);
uchar KeyScan(void);
void delay(uint t);
uchar code segdate[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};     //段选码表
uchar code position[]={0x20,0x10,0x08,0x04,0x02,0x01};       //位选码表
uchar digit[]={6,5,9,5,3,2};     //控制显示的数字
uchar i,j,b=0,temp=4;    //b用来储存P1的值，判断是否可以进行移位和加减，b=1时闪烁
uchar Interruptcount=0;
void delay(uint t)          //延时函数
{ 
	uint n;
	while(t--)
	{
		for(n=0;n<100;n++);
	}
}
void main()
{
	IE=0x83;     //使用外部中断  IE位0为1 位7也为1  1000 0011
	TMOD|=0X01;   //定时器工作方式1
	IT0=0;          //开启外部中断
	TH0=0x3c;         //初值TH0=(65536-45872)/256    50ms
	TL0=0Xb0;         //TL0=(65536-45872)%256
	TR0=1;
	while(1)
	{
		if(b == 0)          //b=0,显示
		{
			display(); 
		}
		if(b == 1)         //b=1,闪烁
		{
			wrinkle();
		}
	}
}
void Time() interrupt 1   //定时器
{
	TR0=0;               //关闭定时器
	TH0=0x3c;  
  TL0=0xb0;
  TR0=1;              //启动定时器
	Interruptcount++;
	if(Interruptcount==20)
	{
		Interruptcount=0;
		if(b == 0)
			carry();
	}
}
void carry(void)  //进位
{
	if(digit[0]<9)         //秒位
	{
		digit[0]++;
	}
	else   //digit[0]=9        
	{
		if(digit[1]<5)         //十秒位
		{
			digit[1]++;
		}
		else //digit[1]=5
		{
			if(digit[2]<9)       //分位
			{
				digit[2]++;
			}
			else //digit[2]=9
			{
				if(digit[3]<5)     //十分位
				{
					digit[3]++;
				}
				else   //digit[3]=5
				{
					if(digit[4]<9 && digit[5]<2)    //19个小时以内
					{
						digit[4]++;
					}
					else if(digit[4]==4 && digit[5]==2)
					{
						digit[4]=0;
					}
					else //digit[4]==9||digit[4]==4
					{
						if(digit[5]<2)
						{
							digit[5]++;
						}
						else  //digit[5]=2
						{
							digit[5]=0;
						}
						digit[4]=0;        //清零
					}
					digit[3]=0;
				}
				digit[2]=0;
			}
			digit[1]=0;
		}
		digit[0]=0;
	}
}
void display(void)    //显示
{
		for(j=0;j<6;j++)
		{
			P1=~position[j];
			if(j==2||j==4)
				{
					P0=segdate[digit[j]]+0x80;
				}
				else 
				{						
					P0=segdate[digit[j]];					
				}
				for(i=1000;i>0;i--);
		}
}
void wrinkle(void)   //闪烁
{	
	
	for(i=50;i>0;i--)
	{
		for(j=0;j<6;j++)
		{
			P1=~position[j];
			if(j==2||j==4)
			{
				P0=segdate[digit[j]]+0x80;
			}
			else 
				P0=segdate[digit[j]];
			delay(1);
		}
	}
	for(i=50;i>0;i--)
	{
		for(j=0;j<6;j++)
		{
			if(j==temp)
			{
				P1=0xff;
			}
			else P1=~position[j];
			if(j==2||j==4)
			{
				P0=segdate[digit[j]]+0x80;
			}
			else
				P0=segdate[digit[j]];
			delay(1);
		}
	}
}
uchar KeyScan(void)   //按键扫描
{
	uchar key;
	if(P2!=0xff)
	{
		for(i=100;i>0;i--)
		if(P2!=0xff)
		{
			key=P2;
		}
		while(P2!=0xff);
	}
	return key;
}
void KeyControl(uchar key)
{
	if(key==0xfe)      //P2^0 按键按下，开启和关闭闪烁
	{
		if(b)
		{
			b=0;
		}
		else 
		{
			b=1;
			temp=5;
		}
	}
	if(b==1)
	{
		if(key==0xfd)      //P2^1按键按下左移
		{
			if(temp<5)
				temp++;
		}
		if(key==0xfb)     //P2^2按键按下右移
		{
			if(temp>0)
				temp--;
		}
		if(key==0xf7)     //P2^3按键按下加
		{
			if(temp==0||temp==2)
			{
				if(digit[temp]<9)
					digit[temp]++;
				else 
					digit[temp]=0;
			}
			else if(temp==1||temp==3)
			{
				if(digit[temp]<5)
					digit[temp]++;
				else 
					digit[temp]=0;
			}
			else if(temp==4&&digit[temp+1]<2)
			{
				if(digit[temp]<9)
					digit[temp]++;
				else
					digit[temp]=0;
			}
			else if(temp==4&&digit[temp+1]==2)
			{
				if(digit[temp]<3)
					digit[temp]++;
				else 
					digit[temp]=0;
			}
			else if(temp==5)
			{
				if(digit[temp]<2)
					++digit[temp];					
				else if(digit[temp]==2)
					{
						if(digit[temp-1]>3)
							digit[temp-1]=0;
						digit[temp]=0;					//达到24小时清零
						}			
			}
		}
		if(key==0xef)  
			{
				if(digit[temp]>0)
					digit[temp]--;
			}
	}
}
void zhonduan() interrupt 0    //外部中断0
{
	KeyControl(KeyScan());
}
				
				
		
			
			
	


			
		
			

	
					
						
						
						
		
	
	