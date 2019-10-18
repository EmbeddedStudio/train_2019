#include <reg51.h>
#include <intrins.h>
void delay(int z)
{unsigned char a,b;
for(a=0;a<200;a++)
for(b=0;b<200;b++);} 
unsigned char Key_Scan();
void main()
{
unsigned char ledValue,keyNum;
ledValue =0x00;
	unsigned  int i;

keyNum = Key_Scan();
switch (keyNum)
{
case(0xFE) :ledValue = 0x01;
break;
case(0xFD) : ledValue = 0x02;
break;
case(0xFB) :ledValue = 0x04;
break;
case(0xF7) :ledValue = 0x08;
break;
case(0xEF) :ledValue = 0x10;
break;
case(0xDF) :ledValue = 0x20;
break;
case(0xBF) :ledValue = 0x40;
break;
case(0x7F) :ledValue = 0x80;
break;
default:break; }
P0= ledValue;}
unsigned char Key_Scan()
{
unsigned char keyValue = 0 ;
if (P2 != 0xFF)
{

unsigned char a,b;
	unsigned  int i;
for(a=0;a<200;a++)
for(b=0;b<200;b++);
if (P2 != 0xFF){
keyValue = P2;
i=0;
while ((i<50)&&(P2 != 0xFF))
{
delay(100); 
i++;
}
}
}
return keyValue; 
}
