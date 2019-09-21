#include "reg51.h"
sbit led=P1^0;
sbit button=P3^2;

int main()
{  IT0 =1;
   IE=0x81;	
   while(1);
	 
}
void TNT0_Handler() interrupt 0
{ 
	if(0==button)
{  int i;
	for(i=100;i>0;i--);
	if(0==button)
{ 
   led =~led;
}
   while(0==button);
}
}	
