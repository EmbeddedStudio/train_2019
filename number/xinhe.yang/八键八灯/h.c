#include "reg51.h"
sbit button0 =P2^0;
sbit button1 =P2^1;
sbit button2 =P2^2;
sbit button3 =P2^3;
sbit button4 =P2^4;
sbit button5 =P2^5;
sbit button6 =P2^6;
sbit button7 =P2^7;
sbit led0 =P0^0;
sbit led1 =P0^1;
sbit led2 =P0^2;
sbit led3 =P0^3;
sbit led4 =P0^4;
sbit led5 =P0^5;
sbit led6 =P0^6;
sbit led7 =P0^7;
int i;
void delay(void)
{	for(i=10000;i>0;i--);}
int main()
{  
 while(1)        
{
    
	
 if( button0==0)
{led0=~led0;delay();}
else if(0 == button1)
{led1=~led1;delay();}
else if(0 == button2)
{led2=~led2;delay();}
else if(0 == button3)
{led3=~led3;delay();}
else if(0 == button4)
{led4=~led4;delay();}
else if(0 == button5)
{led5=~led5;delay();}
else if(0 == button6)
{led6=~led6;delay();}
else if(0 == button7)
{led7=~led7;delay();}
	 }}}