#include <reg52.h>
sbit k1=P3^2;
sbit led=P1^0;
void delay_ms(unsigned int xms);
void key_scan() interrupt 0
{
	if(k1==0)
	{delay_ms(10);
		if(k1==0)
		{
			led=~led;
			while(!k1);
		}
	}
}
void main()
{
	led=1;
	TCON=0x01;
	IE=0x81;
	while(1)
	{
		delay_ms(3000);
	}
}
void delay_ms(unsigned int xms)
{
	unsigned int x,y;
	for(x=xms;x>0;x--)
	for(y=130;y>0;y--);
}