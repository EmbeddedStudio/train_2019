#include<reg51.h>
#define KEY P2;
sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED4 = P0^3;
sbit LED5 = P0^4;
sbit LED6 = P0^5;
sbit LED7 = P0^6;
sbit LED8 = P0^7;					
void main()
{
	P0 = 0XFF;
	P2 = 0xff;
	while(1)
	{
		switch(P2)
		{
			case 0xfe : LED1 = ~LED1;break;
			case 0xfd : LED2 = ~LED2;break;
			case 0xfb : LED3 = ~LED3;break;
			case 0xf7 : LED4 = ~LED4;break;
			case 0xef : LED5 = ~LED5;break;
			case 0xdf : LED6 = ~LED6;break;
			case 0xbf : LED7 = ~LED7;break;
			case 0x7f : LED8 = ~LED8;break;
			default : break;
		}
	}
}
			
