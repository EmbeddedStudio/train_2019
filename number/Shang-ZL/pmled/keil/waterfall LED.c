#include <reg51.h>

sbit led1 = P3^0;
sbit led2 = P3^1;
sbit led3 = P3^2;
sbit led4 = P3^3;
sbit led5 = P3^4;
sbit led6 = P3^5;
sbit led7 = P3^6;
sbit led8 = P3^7;

void delay(int z)
{
	unsigned int i,j;
	for (i=0;i<z;i++)
	{
		j++;
	}
}

int main()
{
	while(1)
	{
		led1 = 1;
	  delay(200);
	  led1 = 0;
	  led2 = 1;
	  delay(200);
	  led2 = 0;
	  led3 = 1;
	  delay(200);
	  led3 = 0;
	  led4 = 1;
	  delay(200);
	  led4 = 0;
	  led5 = 1;
	  delay(200);
	  led5 = 0;
	  led6 = 1;
	  delay(200);
	  led6 = 0;
	  led7 = 1;
	  delay(200);
	  led7 = 0;
	  led8 = 1;
	  delay(200);
	  led8 = 0;
	}
	
	return 0;
}