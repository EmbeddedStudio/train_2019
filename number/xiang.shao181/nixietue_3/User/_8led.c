#include "reg51.h"
typedef unsigned char u8;
typedef unsigned int u16;

char SegCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //0,1,2,3,4,5,6,7,8,9

	
void Timer0Init ()
{
	TMOD |= 0x01;  //�����������֤ǰ��������ܺ�������Ӱ�죬��Ȼ�Ҳ�֪��Ϊʲô
	TH0 = 0xfc;    //th0��ǰ��λ��tl0�Ǻ��λ
	TL0 = 0x18;    //��ֵ�ļ���
	ET0 = 1;       //��t0��ʱ��
	EA = 1;        //�жϵ��ܿ��ص��Ǻ�����ô��Ҫд
	TR0 = 1;       //ǰ��GATE��ֵ��0��������Ϊ����
}

int main()
{
	Timer0Init();
	while(1);
}

void Time0() interrupt 1
{
	static u16 i=0;
	static u16 j;
	TH0 = 0xfc;      //���÷�ʽһÿ�ζ�����������ÿ�ζ�Ҫ���¸���
	TL0 = 0x18;      //�����õĳ�ֵ��һ��һ΢�룬������ʵ��һ��Ҫ����һǧ��
	j=(i/1000);
	if((i%1000==0)&&(i<10000))
	{
		P1 = ~0x01;
    P0 = SegCode[j];
	}
	/*else if(i=10000)
	{
		i=0;
		P1 = ~0x01;
    P0 = SegCode[1];
		delay(500);
		P1 = ~0x02;
		P0 = SegCode[0];
	}*/
	i++;
}
		