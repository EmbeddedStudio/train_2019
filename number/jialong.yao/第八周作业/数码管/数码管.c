#include "reg51.h"  
#define u8 unsigned char 
u8 segcode[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

int main()
{
	int i;
	while(1)
	{
		P1=~0x01;
		P0=segcode[1];
		for(i=1000;i>0;i--);
		P1=~0x02;
		P0=segcode[2]+0x80;
		for(i=1000;i>0;i--);
		P1=~0x04;
		P0=segcode[3];
		for(i=1000;i>0;i--);
		P1=~0x08;
		P0=segcode[4]+0x80;
		for(i=1000;i>0;i--);
		P1=~0x10;
		P0=segcode[5];
		for(i=1000;i>0;i--);
		P1=~0x20;
		P0=segcode[6];
    for(i=1000;i>0;i--);
		
	}
	
}
