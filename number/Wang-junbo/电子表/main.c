#include "reg51.h"
typedef unsigned char u8;
int i,j;
u8 second=3;//秒
u8 minite=50;//
u8 hour=23;//时
u8 mstcnt=0;
u8 DigCode[6]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF};//六个数码挂来诬亮的电位
u8 SegCode[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};//0~9 的十六进制
u8 value[6];//保存每一位数码管显示的数
u8 location=0;//记录具体哪一位在闪烁
sbit  Segment=P0;//P0  控制显示的数
sbit  Digital=P1;//P1  控制哪个灯亮
u8 dispalyCount=5; //控制闪烁间隔
u8 flickerFlag=0;
u8 K1=0;
u8 K2=0;

void delay_ms(int t)//延迟函数
{
	int i,j;
	for(i=t;i>0;i--)
	for(j=1000;j>0;j--);
}	

void display()//数码管显示
{
//Key_Control(Key_Scan());
	 for(j = 0; j > 0; j--) 
	{for(i = 0; i < 6; i++)  
		{P1 = DigCode[i];     
   if(i == 1 || i == 3)                   
   { P0 = SegCode[value[i]] | 0x80;} 
	 else                                  
{P0 = SegCode[value[i]];}             
	delay_ms(1);}
	}                            
	

	for(j = dispalyCount; j > 0; j--)  
	{for(i = 0; i < 6; i++)  
		{if(location == i)   
				 {P1 = 0xff;} 
				 else
					 {P1 = DigCode[i];}
					 if(i == 1 || i == 3)  
						 {P0 = SegCode[value[i]] | 0x80;}
						 else
{P0= SegCode[value[i]];}  
	delay_ms(1);}
	}                           
	} 
	
			
int Key_Scan(void)//按键扫描
{
	int keyValue=0xFF;
	int i=0;
	if(P2!=0xff)
	{
		delay_ms(1);
		if(P2!=0xff)//确认P2改变
		{keyValue=P2;//把按下后的点位给到keyvalue
			while((i<20)&&(P2!=0xff))
			{
			delay_ms(1);
			i++;
			}
		}
	}
	return keyValue;
}


void Key_Control(int keyValue)//按键控制
{
	switch(keyValue)
	{
case(0xfe):	//1111 1110  第一的按键 减
	if(flickerFlag!=0)
	{K1=~K1;}
			break;	
case(0xfd)://1111 1101 第叶二个按键  加
	if(flickerFlag!=0)
	{K2=~K2;}
			break;
case(0xfb):                                           //1111 1011  第三个按键  右移
			if(flickerFlag!=0)
			{
				if(location!=5)
			{location=location+1;}
		}
			break;
case(0xF7):                                            //1111 0111  第四个按键  左移
			if(flickerFlag!=0)
			{
				if(location!=0)
				{location=location-1;}
			}
			break;		
case(0xEF):                                            //1110 1111   第五个按键  闪烁
			flickerFlag=~flickerFlag;
			     break;	
			}	
	}

void time(void)//时间
{
	value[0]=hour/10;
  value[1]=hour%10;
	value[2]=minite/10;
	value[3]=minite%10;
	value[4]=second/10;
	value[5]=second%10;
}
void time_pro(void)//时间进制
	{ 
		if(second==60)                    
          { second=0;
            minite++;
           if( minite==60)              
              { minite=0;
                hour++;
              if(hour==24)              
                 {hour=0; }
							}
					}
  }  
	void TIM0_Handler() interrupt 1//计数
{
	TMOD = 0x01;
     TH0=0x0B;
			TL0=0xDC;
        mstcnt++;
        if(mstcnt==16)
        {
            second++;
            mstcnt=0;    
        }               
			}	
			
void minus()//减
{
	if(K1!=0)
	{
		switch(location)
		{
			case(0):
			{if(hour>=10)
				hour=hour-10;
			 else	
				hour=hour+20;
				}
			break;
			case(1):
			{
				if(hour>9)
				{hour=hour-1;	
				if((hour-9)%10==0)
				hour=hour+10;				
				}
				if(0<hour&&hour<10)
					hour=hour-1;
				else
					hour=9;
			}
			break;
			case(2):
			{if(minite>=10)
			minite=minite-10;
			else
				minite=minite+50;}
			break;
			case(3):
			{
			if(minite>9)
			{
			minite=minite-1;
			if((minite-9)%10==0)
				minite=minite+10;
			}
			if(0<minite&&minite<10)
				minite=minite-1;
			else
				minite=9;
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
				if(second>9)
			{second=second-1;
			if((second-9)%10==0)
			second=second+10;
			}
				if(0<second&&second<10)
				second=second-1;
				else
					second=9;
			}
			break;
		}
	}
		K1=0;
	}

void add()//加
{
if(K2!=0)
	{
		switch(location)
		{
			case(0):
			{hour=hour+10;
			if(hour>30)
				hour=hour-30;
			}
			break;
			case(1):
			{hour=hour+1;
			if(hour%10==0)
				hour=hour-10;
			}
			break;
			case(2):
			{minite=minite+10;
			if(minite>=60)
				minite=minite-60;
			}
			break;
			case(3):
			{minite=minite+1;
				if(minite%10==0)
				minite=minite-10;
			}
			break;
			case(4):
			{second=second+10;
			if(second>=60)
				second=second-60;
		}
			break;
			case(5):
			{second=second+1;
				if(second%10==0)
				second=second-10;
			}
			break;
		}
	K2=0;
	}		
}

void main()//主函数
{
TMOD= 0x01;

	TH0=0x0b;
	TL0=0xdc;
			IE=0x83;
			IT0=1;
	TR0=1;
	while(1)
	{
		minus();
		add();
		time();
		time_pro();
	display();
	}
}
void  INT0_Handler()  interrupt 0 
{
   Key_Control(Key_Scan());
}
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

