#include "reg51.h"
//���Ǹ����������
char SegCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //0,1,2,3,4,5,6,7,8,9

void delay(int i)
{
	int j;
	for(j=i;j>0;j--);
}
		
int main()
{
	int i;
  while(1)
  {
		P1 = ~0x01;
    P0 = 0x06;
    delay(100);
		
    P1 = ~0x02;                 //�������ѡ��ڼ�����ʾ����
    P0 = 0xdb;
    delay(100);
		
		P1 = ~0x04;
		P0 = 0x4f;
		delay(100);
		
		P1 = ~0x08;
		P0 = 0xe6;
		delay(100);
		
		P1 = ~0x10;
    P0 = 0x6d;
    delay(100);
    
    P1 = ~0x20;
		P0 = 0x7d;
		delay(100);
  }
}