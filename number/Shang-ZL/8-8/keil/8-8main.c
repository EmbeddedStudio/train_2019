#include <reg51.h>
sbit led0 = P0^0; //灯的初始化；
sbit led1 = P0^1;
sbit led2 = P0^2;
sbit led3 = P0^3;
sbit led4 = P0^4;
sbit led5 = P0^5;
sbit led6 = P0^6;
sbit led7 = P0^7;

sbit button0 = P2^0; //按键的初始化；
sbit button1 = P2^1;
sbit button2 = P2^2;
sbit button3 = P2^3;
sbit button4 = P2^4;
sbit button5 = P2^5;
sbit button6 = P2^6;
sbit button7 = P2^7;

void delay(int i)  //延迟函数；
{
	for (;i<0;i--);
}

void shanshuo(int i)  //使八个灯闪烁；
{
	  led0 = 1;
	  delay(i);
	  led0 = 0;
		led1 = 1;
	  delay(i);
	  led1 = 0;
	  led2 = 1;
	  delay(i);
	  led2 = 0;
	  led3 = 1;
	  delay(i);
	  led3 = 0;
	  led4 = 1;
	  delay(i);
	  led4 = 0;
	  led5 = 1;
	  delay(i);
	  led5 = 0;
	  led6 = 1;
	  delay(i);
	  led6 = 0;
	  led7 = 1;
	  delay(i);
	  led7 = 0;
	}

int main()     //主函数
{
	while (1)
	{
		shanshuo(200);
		if (0 == button0)     //当按下开关时：
		{
			delay(100);
			if (0 == button0)    
			{
				led0 =~ led0;
			}
			while (0 == button0);
		}
		else if (0 == button1)
		{
			delay(100);
			if (0 == button1)
			{
				led1 =~ led1;
			}
			while (0 == button1);
		}
		else if (0 == button2)
		{
			delay(100);
			if (0 == button2)
			{
				led2 =~ led2;
			}
			while (0 == button2);
		}
		else if (0 == button3)
		{
			delay(100);
			if (0 == button3)
			{
				led3 =~ led3;
			}
			while (0 == button3);
		}
		else if (0 == button4)
		{
			delay(100);
			if (0 == button4)
			{
				led4 =~ led4;
			}
			while (0 == button4);
		}
		else if (0 == button5)
		{
			delay(100);
			if (0 == button5)
			{
				led5 =~ led5;
			}
			while (0 == button5);
		}
		else if (0 == button6)
		{
			delay(100);
			if (0 == button6)
			{
				led6 =~ led6;
			}
			while (0 == button6);
		}
		else if (0 == button7)
		{
			delay(100);
			if (0 == button7)
			{
				led7 =~ led7;
			}
			while (0 == button7);
		}
	}
}