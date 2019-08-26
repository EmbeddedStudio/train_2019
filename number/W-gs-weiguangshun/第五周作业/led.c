#include<reg51.h>

sbit led=P1^0;

int main()
{
	void delay();
while(1)
	{
		led=1;
		delay();
		led=0;
		delay();
	}
return 0 ;
}
void delay()
	{
	 int i;
		for(i=1;i<4600;i++);
	}