#include<reg51.h>
typedef unsigned char uchar;
typedef unsigned int uint;
  
uchar c;

uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void delay(uint i)               //延时函数
{	
	uint a;
	for(a=i;a>0;a--);
}

void display(uchar shu,add1,add2)
{
  uchar shi,ge;
  shi=shu/10;
  ge=shu%10;
  
  P1=add1;
  P0=table[shi];
  delay(50);
  
  P1=add2;
  P0=table[ge];
  delay(50);
}
  
void init()     //初始化函数
{
  TMOD=0x15;              
	TH0=65535/256;
	TL0=65535%256;
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	EA=1;                   
	ET0=1;                   
	ET1=1;
	TR0=1;
	TR1=1;
  display(0,0xbf,0x7f);
  //display(0,0xef,0xdf);
  //display(0,0xfb,0xf7);
}

void main()
{
  uchar min,hour,sec;
  init();
}

void time1() interrupt 3
{
	TH1=(65536-50000)/256;      
	TL1=(65536-50000)%256;
	c++;
}

void time0() interrupt 1        
{
	TH0=65535/256;
	TL0=65535%256;
}