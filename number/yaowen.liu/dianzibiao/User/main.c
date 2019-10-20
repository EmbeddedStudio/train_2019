#include <reg52.h>
#include "bsp_delay.h"

void carry(void);//��λ
void express(void);//��ʾ
void wrinkle(void);//��˸
void Keycontral(u8 key);//����
u8 Keyscan(void);//����ɨ��

unsigned char code distab[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d, 
0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};  //��ѡ���
unsigned char position[6] = {0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//λѡ���
unsigned char digit[6] = {6,5,9,5,3,2};//������ʾ������
unsigned char i,j,b = 0,answer = 4;//b��������P1��ֵ���ж��Ƿ���Խ�����λ�ͼӼ���b=1ʱ��
//����ɨ��˸,����ֹͣ�ߣ�
//b=0ʱֹͣ��˸
unsigned char Interruptcount = 0;

void main()
{
        IE = 0x83;
        TMOD = 0x01;
        IT0 = 1;
        TH0 = 0x0b;
        TL0 = 0xdc;
        TR0 = 1;
        while(1)
        {
                if(b == 0)
                {
                        express();
                }
                if(b == 1)
                {
                        wrinkle();
                }
        }
}

void TIM0_Handler() interrupt 1//��ʱ��
{
        TR0 = 0;
        TH0 = 0x0b;
        TL0 = 0xdc;
        TR0 = 1;
        Interruptcount++;
        if(Interruptcount == 16)
        {
                Interruptcount = 0;
                if(b == 0)
                        carry();
        }
}

void carry(void)//��λ
{
        if(digit[0] < 9)
        {
                digit[0]++;
        }
        else//digit[0] == 9
        {
                if(digit[1] < 5)
                {
                        digit[1]++;
                }
                else//digit[1] == 5
                {
                        if(digit[2] < 9)
                        {
                                digit[2]++;
                        }
                        else//digit[2] == 9
                        {
                                if(digit[3] < 5)
                                {
                                        digit[3]++;
                                }
                                else//digit[3] == 5
                                {
                                        if(digit[4] < 9 && digit[5] < 2)
                                        {
                                                digit[4]++;
                                        }
                                        else if(digit[4] == 4 && digit[5] == 2)
                                        {
                                                digit[4] = 0;
                                        }
                                        else//digit[4] == 9 || digit[4] == 4
                                        {
                                                if(digit[5] < 2)
                                                {
                                                        digit[5]++;
                                                }
                                                else//digit[5] == 2
                                                {
                                                        digit[5] = 0;
                                                }
                                                digit[4] = 0;
                                        }
                                        digit[3] = 0;
                                }
                                digit[2] = 0;
                        }
                        digit[1] = 0;
                }
                digit[0] = 0;
        }
}
void express(void)//��ʾ
{
        for(j = 0;j < 6;j++)
        {
                P2 = position[j];
                if(j == 2 || j == 4)
                {
                        P0 = distab[digit[j]]|0x80;
                }
                else
                {
                        P0 = distab[digit[j]];
                }
                delay(1);
        }
}

void wrinkle(void)//��˸
{
        for(i = 50;i > 0;i--)
        {
                for(j = 0;j < 6;j++)
                {
                        P2 = position[j];
                        if(j == 2 || j == 4)
                        {
                                P0 = distab[digit[j]]|0x80;
                        }
                        else
                                P0 = distab[digit[j]];
                        delay(1);
                }
        }
        for(i = 50;i > 0;i--)
        {
                for(j = 0;j < 6;j++)
                {
                        if(j == answer)
                        {
                                P2 = 0xff;
                        }
                        else
                                P2 = position[j];
                        if(j == 2 || j == 4)
                        {
                                P0 = distab[digit[j]]|0x80;
                        }
                        else
                                P0 = distab[digit[j]];
                        delay(1);
                }
        }
}

u8 Keyscan(void)//����ɨ��
{
        u8 key;
        if(P1 != 0xff)
        {
                for(i = 100;i > 0;i++);
                if(P1 != 0xff)
                {
                        key = P1;
                }
                while(P1 != 0xff);
        }
        return key;
}

void Keycontral(u8 key)//����
{
        if(key == 0xfe)
        {
                if(b)
                {
                        b = 0;
                }
                else
                {
                        b = 1;
                        answer = 5;
                }
        }
        if(b == 1)
        {
                if(key == 0xfd)//����
                {
                        if(answer < 5)
                                answer++;
                }
                if(key == 0xfb)//����
                {
                        if(answer > 0)
                                answer--;
                }
                if(key == 0xf7)//��
                {
                        if(answer == 0 || answer == 2)
                        {
                                if(digit[answer] < 9)
                                        digit[answer]++;
                                else
                                        digit[answer] = 0;
                        }
                        else if(answer == 1 || answer == 3)
                        {
                                if(digit[answer] < 5)
                                        digit[answer]++;
                                else
                                        digit[answer] = 0;
                        }
                        else if(answer == 4 && digit[answer+1] < 2)
                        {
                                if(digit[answer] < 9)
                                        digit[answer]++;
                                else
                                        digit[answer] = 0;
                        }
                        else if(answer == 4 && digit[answer+1] == 2)
                        {
                                if(digit[answer] < 3)
                                        digit[answer]++;
                                else
                                        digit[answer] = 0;
                        }
                        else if(answer == 5)
                        {
                                if(digit[answer] < 2)
                                        ++digit[answer];
                                else if(digit[answer] == 2)
                                {
                                        if(digit[answer-1] > 3)
                                                digit[answer-1] = 0;
                                        digit[answer] = 0;
                                }
                        }
                }
                if(key == 0xef)//��
                {
                        if(digit[answer] > 0)
                                digit[answer]--;
                }
        }
}

void INT0_IRQHander() interrupt 0//�ⲿ�ж�0
{
        Keycontral(Keyscan());
}

//void wrinkle(void)//��˸
//{
//        u8 cont = 1;
//        if(b)
//        {
//                for(j = 0;j < 6;j++)
//                {
//                        P2 = position[j];
//                        if(j == answer && cont < 100)
//                        {
//                                P2 = 0xff;
//                                cont++;
//                        }
//                        else if(j == answer && cont < 200)
//                        {
//                                P2 = position[j];
//                                cont++;
//                        }
//                        else if(j == answer && cont == 200)
//                        {
//                                P2 = position[j];
//                                cont = 1;
//                        }
//                        else
//                        {
//                                P2 = position[j];
//                        }
//                        if(j == 2 || j == 4)
//                        {
//                                P0 = distab[digit[j]]|0x80;
//                        }
//                        else
//                        {
//                                P0 = distab[digit[j]];
//                        }
//                        delay(1);
//                }
//        }
//}
