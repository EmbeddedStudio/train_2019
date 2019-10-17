#include "reg51.h"
#define uchar unsigned char
#define uint unsigned int 
uchar j,k;
sbit KEY0 = P2^0;
sbit KEY1 = P2^1;
sbit KEY2 = P2^2;
uchar code table[] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
void delay(int t)
{
	uchar i;
	while(t--)
	for(i=0;i<125;i++);
}
void keyscan()
{
	while(!KEY0)
	{
		delay(10);
		if(KEY0)  k=1;
	}
	while(!KEY1)
	{
		delay(10);
		if(KEY1) k=2;
	}
	while(!KEY2)
	{
		delay(10);
		if(KEY2) k=3;
	}
}
void main()
{
	IT0=1;
	IE=0x81;
	while(1)
	{
		keyscan();
		switch(k)
		{
			case 1 : 
				for(j=0;j<8;j++)
			{
				keyscan();
				if(k != 1) break;
				P0=table[j];
				delay(500);
			}break;
			case 2 :
				for(j=8;j>0;j--)
			{
				keyscan();
				if(k != 2) break;
				P0=table[j];
				delay(500);
			} break;
			case 3 :
				for(j=0;j<8;j+=2)
			{
				keyscan();
				if(k != 3)  break;
				P0 = table[j];
				delay(500);
			} break;
			default : break;
		}
	}
}
void zhongduan() interrupt 0
{
	kescan();
}