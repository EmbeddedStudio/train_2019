#include <reg51.h>

sbit led = P1^7;

void delay(int a)
{
	int i;
	for (i = 1;i<a;i++);
}

int main()
{
	while(1)
	{
		led = 1;
		delay(7500);
		led = 0;
		delay(7500);
	}
	return 0;
}
	