#include "reg51.h"
typedef unsigned char u8;
typedef unsigned int u16;

void keycontral(u8 key);
u8 keycan();
void carry();
void express();
void wrinkle();
void inter();
void delay(u16 i);

u8 table1[6] = {1,1,5,9,5,7};//���ó�ֵ
u8 table2[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//λѡ
u8 table3[6] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20};//��ѡ

u8 c=0;   //��������ʱ��Ķ���
u8 b=0,a=4,i,j;   //b�������������Ի�����˸��

void delay(u16 i) //��ʱ����
{
  for(;i>0;i--);
}

void inter()    //�жϵĳ�ʼ��
{
  IE = 0x83;
  TMOD = 0x01;
  IT0 = 1;
  TH0 = 0x0b;
  TL0 = 0xdc;
  TR0 = 1;
}  

void main()
{
  inter();
  while(1)
  {
    if(b==0)
    {
      express();   //���Ժ���
    }
    if(b==1)
    {
      wrinkle();   //��˸����
    }
  }
}

void time1()   interrupt 1
{
  TR0 = 0;
  TH0 = 0x0b;
  TL0 = 0xdc;
  TR0 = 1;
  c++;
  if(c==16)
  {
    c=0;        //һ������ȻҪ������
    if(b==0)
      carry();
  }
}

void carry()   //��λ����
{
  if(table1[5]<9)
  {
    table1[5]++;
  }
  else
  {
    if(table1[4]<5)
    {
      table1[4]++;
    }
    else
    {
      if(table1[3]<9)
      {
        table1[3]++;
      }
      else
      {
        if(table1[2]<5)
        {
          table1[2]++;
        }
        else
        {
          if(table1[1]<9&&table1[5]<2)
          {
            table1[1]++;
          }
          else if(table1[1] < 3 && table1[0] ==2)
          {
            table1[1]++;
          }
          else
          {
            if(table1[0]<2)
            {
              table1[0]++;
            }
            else
            {
              table1[0]=0;
            }
            table1[1]=0;
          }
          table1[2]=0;
        }
        table1[3]=0;
      }
      table1[4]=0;
    }
    table1[5]=0;
  }
}

void express() //���Ժ���
{
//  P1=~0x10;
//  P0=table2[table1[2]];

  for(i=0;i<6;i++)
  {
    P1=~table3[i];
    if(i==1 || i==3 || i==5 )
    {
      P0=table2[table1[i]]|0x80;
    }
    else
    {
      P0 = table2[table1[i]];
    }
    delay(500);
  }
}

void wrinkle()   //��˸����
{
  for(j=50;j>0;j--)
  {
    for(i=0;i<6;i++)
    {
      P1=~table3[i];
      if(i==1 || i==3 || i==5)
      {
        P0=table2[table1[i]]|0x80;
      }
      else
      {
        P0 = table2[table1[i]];
      }
      delay(50);
    }
  }
  for(j=50;j>0;j--)
  {
    for(i=0;i<6;i++)
    {
      if(i==a)
      {
        P1=~0x00;
      } 
      else
      {
        P1 =~table3[i];
      }
      if(i==1 || i==3 || i==5)
      {
        P0=table2[table1[i]]|0x80;
      }
      else
      {
        P0=table2[table1[i]];
      }
      delay(50);
    }
  }
}

u8 keycan()//�������
{
  u8 key;
//  if(P2 != 0xff)
//  {
//    for(i=100;i>0;i++);
//    if(P2 != 0xff)
//    {
//      key = P1;
//    }
//    while(P2 != 0xff);
//  }
  key=P2;
  return key;
}

void keycontral(u8 key)
{
//  if(key == 0xfe)
//  {
//    b=1;
//  }
  if(key ==0xfe)
  {
    if(b)  //�����ڼ�����٣���Ϊ��Ϊ��ִ�к�����
    {
      b=0;
    }
    else
    {
      b=1;
      a=5; //���¶�ֵ��֪����������
    }
  }
  if(b==1)   //˵�˰�Ҫ��һ�ε�һ����
  {
    if(key == 0xfd) //����P2^1
    {
      if(a<5)
      {
        a++;
      }
    }
    if(key == 0xfb) //����P2^2
    {
      if(a>0)
      {
        a--;
      }
    }
    if(key == 0xf7) //��P2^3
    {
      if(a == 3|| a == 5)
      {
        if(table1[a]<9)
          table1[a]++;
        else
          table1[a]=0;
      }
      else if(a == 2 || a == 4)
      {
        if(table1[a]<5)
          table1[a]++;
        else
          table1[a] = 0;
      }
      else if(a == 1 && table1[a-1]<2)
      {
        if(table1[a]<9)
        {
          table1[a]++;
        }
        else
        {
          table1[a]=0;
        }
      }
      else if(a == 1 && table1[a-1] == 2)
      {
        if(table1[a] < 3)
        {
          table1[a]++;
        }
        else
        {
          table1[a]=0;
        }
      }
      else if(a==0)
      {
        if(table1[a] < 2)
        {
          table1[a]++;
        }
        else if(table1[a] == 2)
        {
          table1[a] = 0;
        }
      }
   }
    if(key == 0xef) //��P2^4
    {
//      if(a==3||a==5)
//      {
//        if(table1[a]>0)
//          table1[a]--;
//        else
//          table1[a]=0;
//      }
      if(table1[a] > 0)
        table1[a]--;
    }
  }
}

void time2() interrupt 0  //�����ж�
{
   keycontral(keycan());
}