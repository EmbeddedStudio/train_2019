#include "reg51.h"
#define uchar unsigned char
#define uint unsigned int
void carry(void);
void display(void);
void wrinkle(void);
void KeyControl(uchar key);
uchar KeyScan(void);
void delay(uint t);
uchar code segdate[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};     //��ѡ���
uchar code position[]={0x20,0x10,0x08,0x04,0x02,0x01};       //λѡ���
uchar digit[]={6,5,9,5,3,2};     //������ʾ������
uchar i,j,b=0,temp=4;    //b��������P1��ֵ���ж��Ƿ���Խ�����λ�ͼӼ���b=1ʱ��˸
uchar Interruptcount=0;
void delay(uint t)          //��ʱ����
{ 
	uint n;
	while(t--)
	{
		for(n=0;n<100;n++);
	}
}
void main()
{
	IE=0x83;     //ʹ���ⲿ�ж�  IEλ0Ϊ1 λ7ҲΪ1  1000 0011
	TMOD|=0X01;   //��ʱ��������ʽ1
	IT0=0;          //�����ⲿ�ж�
	TH0=0x3c;         //��ֵTH0=(65536-45872)/256    50ms
	TL0=0Xb0;         //TL0=(65536-45872)%256
	TR0=1;
	while(1)
	{
		if(b == 0)          //b=0,��ʾ
		{
			display(); 
		}
		if(b == 1)         //b=1,��˸
		{
			wrinkle();
		}
	}
}
void Time() interrupt 1   //��ʱ��
{
	TR0=0;               //�رն�ʱ��
	TH0=0x3c;  
  TL0=0xb0;
  TR0=1;              //������ʱ��
	Interruptcount++;
	if(Interruptcount==20)
	{
		Interruptcount=0;
		if(b == 0)
			carry();
	}
}
void carry(void)  //��λ
{
	if(digit[0]<9)         //��λ
	{
		digit[0]++;
	}
	else   //digit[0]=9        
	{
		if(digit[1]<5)         //ʮ��λ
		{
			digit[1]++;
		}
		else //digit[1]=5
		{
			if(digit[2]<9)       //��λ
			{
				digit[2]++;
			}
			else //digit[2]=9
			{
				if(digit[3]<5)     //ʮ��λ
				{
					digit[3]++;
				}
				else   //digit[3]=5
				{
					if(digit[4]<9 && digit[5]<2)    //19��Сʱ����
					{
						digit[4]++;
					}
					else if(digit[4]==4 && digit[5]==2)
					{
						digit[4]=0;
					}
					else //digit[4]==9||digit[4]==4
					{
						if(digit[5]<2)
						{
							digit[5]++;
						}
						else  //digit[5]=2
						{
							digit[5]=0;
						}
						digit[4]=0;        //����
					}
					digit[3]=0;
				}
				digit[2]=0;
			}
			digit[1]=0;
		}
		digit[0]=0;
	}
}
void display(void)    //��ʾ
{
		for(j=0;j<6;j++)
		{
			P1=~position[j];
			if(j==2||j==4)
				{
					P0=segdate[digit[j]]+0x80;
				}
				else 
				{						
					P0=segdate[digit[j]];					
				}
				for(i=1000;i>0;i--);
		}
}
void wrinkle(void)   //��˸
{	
	
	for(i=50;i>0;i--)
	{
		for(j=0;j<6;j++)
		{
			P1=~position[j];
			if(j==2||j==4)
			{
				P0=segdate[digit[j]]+0x80;
			}
			else 
				P0=segdate[digit[j]];
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
			else P1=~position[j];
			if(j==2||j==4)
			{
				P0=segdate[digit[j]]+0x80;
			}
			else
				P0=segdate[digit[j]];
			delay(1);
		}
	}
}
uchar KeyScan(void)   //����ɨ��
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
	if(key==0xfe)      //P2^0 �������£������͹ر���˸
	{
		if(b)
		{
			b=0;
		}
		else 
		{
			b=1;
			temp=5;
		}
	}
	if(b==1)
	{
		if(key==0xfd)      //P2^1������������
		{
			if(temp<5)
				temp++;
		}
		if(key==0xfb)     //P2^2������������
		{
			if(temp>0)
				temp--;
		}
		if(key==0xf7)     //P2^3�������¼�
		{
			if(temp==0||temp==2)
			{
				if(digit[temp]<9)
					digit[temp]++;
				else 
					digit[temp]=0;
			}
			else if(temp==1||temp==3)
			{
				if(digit[temp]<5)
					digit[temp]++;
				else 
					digit[temp]=0;
			}
			else if(temp==4&&digit[temp+1]<2)
			{
				if(digit[temp]<9)
					digit[temp]++;
				else
					digit[temp]=0;
			}
			else if(temp==4&&digit[temp+1]==2)
			{
				if(digit[temp]<3)
					digit[temp]++;
				else 
					digit[temp]=0;
			}
			else if(temp==5)
			{
				if(digit[temp]<2)
					++digit[temp];					
				else if(digit[temp]==2)
					{
						if(digit[temp-1]>3)
							digit[temp-1]=0;
						digit[temp]=0;					//�ﵽ24Сʱ����
						}			
			}
		}
		if(key==0xef)  
			{
				if(digit[temp]>0)
					digit[temp]--;
			}
	}
}
void zhonduan() interrupt 0    //�ⲿ�ж�0
{
	KeyControl(KeyScan());
}
				
				
		
			
			
	


			
		
			

	
					
						
						
						
		
	
	