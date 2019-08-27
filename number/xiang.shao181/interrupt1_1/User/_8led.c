#include "reg51.h"

sbit led=P0^0;
sbit key=P3^2;

void delay(int i)
{
	while(i>=0)
	{
		i--;
	}
}

int main()
{
	IT0=1;
	IE=0x81;
	while(1);
}

void into() interrupt 0
{
	delay(1000);
	if(key==0);
	{
		led=~led;
	}
}