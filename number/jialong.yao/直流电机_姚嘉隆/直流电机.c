#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit KEY0=P2^0;
sbit KEY1=P2^1;
sbit KEY2=P2^2;
sbit KEY3=P2^3;
sbit IN1=P2^4;
sbit IN2=P2^5;
uchar num=0,show_num=1,high_num=1,low_num=4,num1;           //初始PMW的占空比为20%
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
void delay(uint t)
{
	uint i;
	while(t--)
	{
		for(i=120;i>0;i--);
	}
}
void keyscan()
{
	if(KEY0 == 0)       //正转
	{
		delay(10);
		if(KEY0 == 0)      
		{
			IN1=0;
			IN2=1;
			num1=1;
			while(!KEY0);
		}
	}
	if(KEY1 == 0)     //反转
	{
		delay(10);
		if(KEY1 == 0)
		{
			IN1=1;
			IN2=0;
			num1=0;
			while(!KEY1);
		}
	}
	if(KEY2 == 0)      //加速
	{
		delay(10);
		if(KEY2 == 0)
		{
			num++;
			if(num == 5)
			{
				num = 4;
			}
			while(!KEY2);
		}
	}
	if(KEY3 == 0)         //减速
	{
		delay(10);
		if(KEY3 == 0)
		{
			if(num != 0)
				num--;
			else 
				num = 0;
			while(!KEY3);
		}
	}
}
void display()      //显示函数
{
	P1=~0x02;         //第一个数码管显示正转(1)还是反转(0)
	P0=table[num1];
	delay(5);
	P1=~0x01;
	P0=table[show_num];       //第二个数码管显示速度标志
	delay(5);
}
void dispose()
{
	switch(num)
	{
		case 0 : show_num=1; high_num=1; low_num=4; break;
		case 1 : show_num=2; high_num=2; low_num=3; break;
		case 2 : show_num=3; high_num=3; low_num=2; break;
		case 3 : show_num=4; high_num=4; low_num=1; break;
		default: break;
	}
}
void kongzhi()    //控制电机程序
{
	uchar x;
	if(num1 == 1)     //正转占空比调节
	{
		if(low_num != 0)
		{
			for(x=0;x<low_num;x++)
			{
				IN1 = 1; 				//PWM低电平输出
				display();         //显示函数延时
			}
		}
		for(x=0;x<high_num;x++)
		{
			IN1 = 0;           //PMW高电平输出			
			display();
		}
	}
	if(num1 == 0)        //反转占空比调节
	{
		if(low_num != 0)
		{
			for(x=0;x<low_num;x++)
			{				
				IN2 = 1;
				display();
			}
		}
		for(x=0;x<high_num;x++)
		{			
			IN2 = 0;
			display();
		}
	}
}
void main()
{
	while(1)
	{
		keyscan();
		dispose();
		kongzhi();
	}
}
	
		
			
				
				
	
	
	
			
			
