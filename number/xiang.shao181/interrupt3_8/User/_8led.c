#include "reg51.h"

#define led P0
sbit key=P2;

int keyvalue=0xff;
int ledvalue=0;
int led2=0xfe;

void delay(int i)
{
	while(i>=0)
	{
		i--;
	}
}

void into() interrupt 0
{
	if(key!=keyvalue)
	{
		delay(1);
		if(key!=keyvalue)
		{
			switch(P2)
			{
				case(0xfe):
					if(led2!=0xfe)
					{
						led2=~(~(led2)>>1);
					}
					break;
				case(0xfd):
					ledvalue=~ledvalue;
					break;
				case(0xfb):
					if(led2!=0x8f)
					{
						led2=~(~(led2)<<1);
					}
					break;
			}
		}
	}
}

int main()
{
	IT0=1;
	IE=0x81;
	
	key=keyvalue;
	
	while(1)
	{
		led=led2;
		if(ledvalue!=0)
		{
			delay(1);
			if(ledvalue!=0)
			{
				led=0xff;
				delay(20);
			}
		}
	}
}
