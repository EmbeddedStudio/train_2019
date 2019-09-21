#include <reg51.h>
#include <intrins.h>
sbit p1=P1^0;
void delay(void)
{
	int a=500;
	int i;
	for(i=0;i<a;i++);
}
void INT0_srv(void) interrupt 0 using 1
{
delay();
	if(INT0==0)
	{
		p1=! p1;
   while (INT0==0);
	}
 }
void main()
{
p1=0;
	EA=1;
	EX0=1;                                    
	while(1);
}
