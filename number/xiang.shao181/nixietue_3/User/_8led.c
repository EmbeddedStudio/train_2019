#include "reg51.h"
typedef unsigned char u8;
typedef unsigned int u16;

char SegCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //0,1,2,3,4,5,6,7,8,9

	
void Timer0Init ()
{
	TMOD |= 0x01;  //这个货用来保证前面的数不受后面数的影响，虽然我不知道为什么
	TH0 = 0xfc;    //th0是前八位，tl0是后八位
	TL0 = 0x18;    //初值的计算
	ET0 = 1;       //打开t0定时器
	EA = 1;        //中断的总开关但是好像不怎么需要写
	TR0 = 1;       //前面GATE的值是0；所以人为控制
}

int main()
{
	Timer0Init();
	while(1);
}

void Time0() interrupt 1
{
	static u16 i=0;
	static u16 j;
	TH0 = 0xfc;      //利用方式一每次都会重置所以每次都要重新复制
	TL0 = 0x18;      //这里用的初值是一次一微秒，所以想实现一秒要运行一千次
	j=(i/1000);
	if((i%1000==0)&&(i<10000))
	{
		P1 = ~0x01;
    P0 = SegCode[j];
	}
	/*else if(i=10000)
	{
		i=0;
		P1 = ~0x01;
    P0 = SegCode[1];
		delay(500);
		P1 = ~0x02;
		P0 = SegCode[0];
	}*/
	i++;
}
		