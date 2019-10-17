#include "reg51.h"
#define uchar unsigned char
#define uint unsigned int
void add(void);
void display(void);
void change(void);
void KeyControl(uchar key);
uchar KeyScan(void);
void delay(uint t);
uchar code segment[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};     //????
uchar code position[]={~0x01,~0x02,~0x04,~0x08,~0x10,~0x20};       //????
uchar digcode[]={0,0,0,0,0,0};     //???????
uchar i,j,a=0,temp=5;    //b????P1??,?????????????,b=1???
uchar Interruptcount=0;
//int time,time1,time2,time3,time4,time5,time6;
void delay(uint t)          //????`
{ 
	uint n;
	while(t--)
	{
		for(n=0;n<100;n++);
	}
}
void main()
{
	IE=0x83;     //??????  IE?0?1 ?7??1  1000 0011
	TMOD|=0X01;   //???????1
	IT0=1;          //??????
	TH0=0x0b;         //??TH0=(65536-45872)/256    50ms
	TL0=0Xdc;         //TL0=(65536-45872)%256
	TR0=1;
	while(1)
	{
		if(a == 0)          //b=0,??
		{
			display(); 
			
		}
//		 add();
		if(a == 1)         //b=1,??
		{
			change();
		}
	}
}
void Time() interrupt 1   //???
{
	TR0 = 0;          
   TH0 = 0x0b;    
	 TL0 = 0xdc;          
	 TR0 = 1;              
	 Interruptcount++;
	 if(Interruptcount >= 16) 
	{
		Interruptcount=0;
		if(a == 0)
		{
//			time++;
			add();
			
		}	
	}
}

void add(void)  //??
{
	if(digcode[5]<9)         //??
	{
		digcode[5]++;
	}
	else   //digit[0]=9        
	{
		if(digcode[4]<5)         //???
		{
			digcode[4]++;
			digcode[5]=0;
		}
		else //digit[1]=5
		{
			if(digcode[3]<9)       //??
			{
				digcode[3]++;
				digcode[4]=0;
				digcode[5]=0;
			}
			else //digit[2]=9
			{
				if(digcode[2]<5)     //???
				{
					digcode[2]++;
					digcode[3]=0;
					digcode[4]=0;
				  digcode[5]=0;
				}
				else   //digit[3]=5
				{
					if(digcode[1]<9 && digcode[0]<2)    //19?????
					{
						digcode[1]++;
						digcode[2]=0;
						digcode[3]=0;
					  digcode[4]=0;
				    digcode[5]=0;
					}
					else if(digcode[1]==3 && digcode[0]==2)
					{
						digcode[1]=0;
						digcode[0]=0;
					}
					else //digit[4]==9||digit[4]==4
					{
						if(digcode[0]<2 )
						{
							digcode[0]++;
							digcode[1]=0;
						}
						else  //digit[5]=2
						{
							digcode[5]=0;
						}
//						digcode[4]=0;        //??
					}
//					digcode[3]=0;
				}
//				digcode[2]=0;
			}
//			digcode[1]=0;
		}
//		digcode[0]=0;
	}
}
void display(void)    //??
{
		for(j=0;j<6;j++)
		{
			P1=position[j];
			if(j==1||j==3)
				{
					P0=segment[digcode[j]]| 0x80;
				}
				else 
				{						
					P0=segment[digcode[j]];					
				}
				delay(1);
		}
}
void change(void)   //??
{	
	
	for(i=50;i>0;i--)
	{
		for(j=0;j<6;j++)
		{
			P1=position[j];
			if(j==1||j==3)
			{
				P0=segment[digcode[j]]|0x80;
			}
			else 
				P0=segment[digcode[j]];
			delay(1);
		}
	}
	for(i=50;i>0;i--)
	{
		for(j=0;j<6;j++)
		{
			if(j==temp)
			{
				P1=0xff;
			}
			else P1=position[j];
			if(j==1||j==3)
			{
				P0=segment[digcode[j]]|0x80;
			}
			else
				P0=segment[digcode[j]];
			delay(1);
		}
	}
}
uchar KeyScan(void)   //????
{
	uchar key;
	if(P2!=0xff)
	{
		for(i=100;i>0;i--)
		if(P2!=0xff)
		{
			key=P2;
		}
		while(P2!=0xff);
	}
	return key;
}
void KeyControl(uchar key)
{
	if(key==0xfe)      //P2^0 ????,???????
	{
		if(a)
		{
			a=0;
		}
		else 
		{
			a=1;
			temp=5;
		}
	}
	if(a==1)
	{
		if(key==0xfd)      //P2^1??????
		{
			if(temp<5)
				temp++;
		}
		if(key==0xfb)     //P2^2??????
		{
			if(temp>0)
				temp--;
		}
		if(key==0xf7)     //P2^3?????
		{
			if(temp==5||temp==3)
			{
				if(digcode[temp]<9)
					digcode[temp]++;
				else 
					digcode[temp]=0;
			}
			else if(temp==4||temp==2)
			{
				if(digcode[temp]<5)
					digcode[temp]++;
				else 
					digcode[temp]=0;
			}
			else if(temp==0&&digcode[temp]<2)
			{
				
					digcode[temp]++;
			}
				else
					digcode[temp]=0;
			}
			/*else if(temp==1&&digcode[temp]<4)
			{
				
					digcode[temp]++;
				else 
					digcode[temp]=0;
			}
			else if(temp==5)
			{
				if(digcode[temp]<2)
					++digcode[temp];					
				else if(digcode[temp]==2)
					{
						if(digcode[temp-1]>3)
							digcode[temp-1]=0;
						digcode[temp]=0;					//??24????
						}			
			}*/
		}
		if(key==0xef)  
			{
				if(digcode[temp]>0)
					digcode[temp]--;
			}
	}

void zhonduan() interrupt 0    //????0
{
	KeyControl(KeyScan());
}
	 
		 
					 
				 
								
								
				
				