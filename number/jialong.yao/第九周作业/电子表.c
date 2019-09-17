#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar code segdate[]={0X3f,0X06,0X5B,0X4f,0X66,0X6d,0X7d,0X07,0X7f,0X6f,};
void main()
{
	RCAP2H = 0X10;     //赋T2的预置值为0x1000，溢出30次就是1s
	RCAP2L = 0X00;      
	TR2=1;             //启动定时器
	ET2=1;             //打开定时器2中断
	EA=1;              //打开总中断
	while(1)
	{
		;
	}
}
void display()
{
	static uchar j=1,k=0,m;
	P1=~0x01;
		P0=segdate[j];
		j++;
		k++;
		if(k>9)
		{
			while(1)
				{
					P1=~0x01;
			    P0=segdate[1];
					for(m=1000;m>0;m--);
					
			    P1=~0x02;
			    P0=segdate[0];
					for(m=1000;m>0;m--);
	      }
			}
		}
void Timer0() interrupt 5
{
	static uchar i;
	TF2=0;
	i++;
	if(i==30)
	{
		i=0;
		display();
	 }
	}

			
				
		
		
