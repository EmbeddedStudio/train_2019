#include <reg51.h>
#include <intrins.h>
sbit p1_0=P1^0;
void delay (void)
{
	int a=5000;
	while(a--)_ncp_();
}
void INT0_srv (void)©iinterrupt 0 using 1
{
	delay();
	if(INT0==0)
	{
		p1_0=!p1_0;
		while(INT0= =0);
	}
}
	void main()
	{
		p1_0=0;
		EA=1;
		EX0=1;
		while(1);
	}