#include <reg51.h>
int dispalyCount;
int location=0;
int flash=0;
int value[6];
int i=0,j=0,k=0,second=0,minute=0,hour=0;
typedef unsigned char U10;
U10 moment=0;
U10 SegCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
U10 DigCode[6]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF};

void delay(int t)
{
	int i,j;
	for(i=t;i>0;i--)
	for(j=1000;j>0;j--);
}




void time_cut() interrupt 1 
{
TR0=0;
TH0=0X0b;
TL0=0Xdc;
TR0=1;
moment++;
if(moment==16)
{
moment=0;	
second++;
}
}




void time_calculate()
{
	if(second>=59)
	{
	second=0;
	minute++;
	}
	if(minute>=59)
	{
	minute=0;
	hour++;
	}
	if(hour>=23)
	{
	hour=0;
	}
}






void time_display()
{ 
		 value[0]=hour/10;
	   value[1]=hour%10;
     value[2]=minute/10;
	   value[3]=minute%10;
     value[4]=second/10;
     value[5]=second%10;
for(j = 5; j > 0; j--) 
{
for(i = 0; i < 6; i++)
{
P1 = DigCode[i];
if(i == 1 || i == 3)
{
P0 = SegCode[value[i]] | 0x80;
}
else
{
P0 = SegCode[value[i]];
}
delay(1);
}
}
for(j = dispalyCount; j > 0; j--) 
{
for(i = 0; i < 6; i++)
{
if(location == i)
{
P1 = 0xff;
}
else
{
P1 = DigCode[i];
}
if(i == 1 || i == 3)
{
P0 = SegCode[value[i]] | 0x80;
}
else
{
P0 = SegCode[value[i]];
}
delay(1);
}
}
}



int Key_Scan(void)
{
int keyValue = 0xff;
int i = 0;
if(P2 != 0xff)
{
delay(1);
if(P2 != 0xff)
{
keyValue = P2;
while((i < 20) && (P2 != 0xff))
{
delay(1);
i++;
}
} 
}
return keyValue;
}








void key_control(int keyValue)
{
switch(keyValue)
{
case(0xfe): //让其进入闪烁阶段，一次进入一次退出。
{
TR0=~TR0;
flash = ~flash;
}
break;

case(0xfd)://让其右移。
{
location=location+1;
if(location==6)
location=0;
}
break;

case(0xfb): //让其左移。
{
if(flash !=0)
{
location=location-1;
if(location==-1)
location=5;
}
}
break;

case(0xf7)://在闪烁的地方加一.
{
if(flash !=0)
{
switch(location)
{
case(0):
{
	hour=hour+10;
//if(hour>20)
//{hour=hour-10;
//value[0]=0;
}
break;
case(1):
{
hour=hour+1;
if(value[1]==9)
{value[1]=0;
hour=hour-10;
}
}
break;
case(2):
{
minute=minute+10;
if(value[2]==5)
{
value[2]=0;
hour = hour-1;
}
}
break;

case(3):
{
minute=minute+1;
if(value[3]==9)
{value[3]=0;
minute=minute-10;
}
}
break;

case(4):
{
second=second+10;
if(value[4]==5)
{
value[4]=0;
minute=minute-1;
}
}
break;

case(5):
{
second=second+1;
if(value[5]==9)
{value[5]=0;
second=second-10;
}
}
break;
}
}
}
break;

case(0xef)://让其在闪烁的地方减一。
{
if(flash!=0)
{
switch(location)
{
case(0):
{
if(hour<10)
hour=hour+20;
else
{
if(hour>10)
hour=hour-10;
else
hour=hour-1;
}
}
break;

case(1):
{
hour=hour-1;
if(value[1]==0)
{value[1]=9;
hour=hour+10;
}
}
break;

case(2):
{
minute=minute-10;
if(value[2]==0)
{
value[2]=5;
minute=minute+60;
}
}
break;

case(3):
{
minute=minute-1;
if(value[3]==0)
{value[3]=9;
minute=minute+10;
}
}
break;

case(4):
{
if(second>=10)
second=second-10;
if(value[4]==0)
{
value[4]=5;
if(second<10)
second=second+50;
else
second=second+10;
}
}
break;

case(5):
{
second=second-1;
if(value[5]==0)
{second=9;
}
}
break;

}
}
break;
default:
break;
}
}
}


void main()//kiss1 开始闪烁   kiss2 右移  kiss3 左移  kiss4 加一  kiss5 减一  
{
IE=0X83;
TMOD=0X01;
TH0=0X0b;
TL0=0Xdc;
TR0=1;
while(1)
{
key_control(Key_Scan());
time_calculate();
time_display();
if(flash!=0)
dispalyCount=6;
else
dispalyCount=0;
}
}




