#include "reg51.h" 
typedef unsigned char u8;
u8 DigCode[6]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF};
u8 SegCode[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
u8 value[6]={1, 2, 3, 4, 5, 6};
u8 location=0;
u8 flickerFlag=0;
u8 dispalyCount=0;
u8 second=0;
u8 minute=0;
u8 hour=0;
u8 InterruptCount=0;
u8 Li1=0;
u8 Li2=0;
int i,j;

void delay(int z)
{
	int i;
	for(i=100;i>=0;i--)
	for(;z>=0;z--);
}
int Key_Scan(void);
void Key_Control(int keyValue);
void shijian(void);
void jinzhi(void);
void jian();
void jia();
void changliang()
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
void shanshuo()
{
	for(j = 20; j > 0; j--)
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
for(j = 20; j > 0; j--) 
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
void main()
{
TMOD= 0x01;

	TH0=0x0b;
	TL0=0xdc;
			IE=0x83;
			IT0=1;
	TR0=1;

	while(1)
	{
	
		 jian();
		 jia();
		 shijian();
		 jinzhi();
		if(flickerFlag==0)
			changliang();
		else
			shanshuo();
		 
	 }
	}
int Key_Scan(void)
{
int keyValue=0xff;
int i = 0;
	if(P2!=0xff)
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
void Key_Control(int keyValue)
{
switch(keyValue)
{
	case(0xfe):
	if(flickerFlag!=0)
  {
	Li1=~Li1;
	}	
  break;
	case(0xfd):
		if(flickerFlag!=0)
		{
		Li2=~Li2;
		}
		break;
		case(0xfb):
			if(flickerFlag!=0)
			{
			if(location!=5)
			{
			location++;
			}
		}
			break;
			case(0xf7):
			if(flickerFlag!=0)
			{
				if(location!=0)
				{
				location--;
				}
			}
				break;
				case(0xef):
					flickerFlag=~flickerFlag;
				break;

}
}
void shijian(void)
{
value[0]=hour/10;
value[1]=hour%10;
	value[2]=minute/10;
	value[3]=minute%10;
	value[4]=second/10;
	value[5]=second%10;
}
void jinzhi(void)
{
if(second==60)
{
second=0;
	minute++;
}
	if(minute==60)
{
minute=0;
	hour++;
}
	if(hour==24)
{
hour=0;
}
}
void TIM0_Handler() interrupt 1
{

 TR0 = 0; 
	 TH0 = 0x0b; 
	 TL0 = 0xdc;
	 TR0 = 1;
	InterruptCount++;
	 if(InterruptCount >= 16)
	 {
		 InterruptCount = 0;
      second++;

 }
}
void jian()
{
if(Li1!=0)
	{
		switch(location)
		{
			case(0):
			{
				if(hour>=10)
				hour=hour-10;
			 else	
				hour=hour+20;
				}
			break;
			case(1):
			{
				if(0<hour&&hour<10)
					hour--;
				else
					hour=9;
			}
			break;
			case(2):
			{
				if(minute>=10)
			minute=minute-10;
			else
				minute=minute+50;}
			break;
			case(3):
			{
			if(0<minute&&minute<10)
				minute=minute-1;
			else
				minute=9;
		}
			break;
			case(4):
			{if(second>=10)
			second=second-10;
			else
				second=second+50;
			}
			break;
			case(5):
			{
				if(0<second&&second<10)
				second=second-1;
				else
					second=9;
			}
			break;
		}
	}
		Li1=0;
	}
void jia()
{
if(Li2!=0)
	{
		switch(location)
		{
			case(0):
			{
				hour=hour+10;
			if(hour>=30)
				hour=hour-30;
			}
			break;
			case(1):
			{
				hour++;
			if(hour%10==0)
				hour=hour-10;
			}
			break;
			case(2):
			{
				minute=minute+10;
			if(minute>=60)
				minute=minute-60;
			}
			break;
			case(3):
			{
				minute++;
				if(minute%10==0)
				minute=minute-10;
			}
			break;
			case(4):
			{
				second=second+10;
			if(second>=60)
				second=second-60;
		}
			break;
			case(5):
			{
				second++;
				if(second%10==0)
				second=second-10;
			}
			break;
		}
	Li2=0;
	}
}
void  INT0_Handler()  interrupt 0 
{
   Key_Control(Key_Scan());
}