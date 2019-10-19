#include <reg52.h>
#include "bsp_delay.h"

void carry(void);//进位
void express(void);//显示
void wrinkle(void);//闪烁
void Keycontral(u8 key);//操作
u8 Keyscan(void);//按键扫描

unsigned char code distab[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d, 
0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};  //段选码表
unsigned char position[6] = {0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//位选码表
unsigned char digit[6] = {6,5,9,5,3,2};//控制显示的数字
unsigned char i,j,b = 0,answer = 4;//b用来储存P1的值，判断是否可以进行移位和加减，b=1时闪
//按键扫描烁,并且停止走，
//b=0时停止闪烁
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

void TIM0_Handler() interrupt 1//定时器
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

void carry(void)//进位
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
void express(void)//显示
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

void wrinkle(void)//闪烁
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

u8 Keyscan(void)//按键扫描
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

void Keycontral(u8 key)//操作
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
                if(key == 0xfd)//左移
                {
                        if(answer < 5)
                                answer++;
                }
                if(key == 0xfb)//右移
                {
                        if(answer > 0)
                                answer--;
                }
                if(key == 0xf7)//加
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
                if(key == 0xef)//减
                {
                        if(digit[answer] > 0)
                                digit[answer]--;
                }
        }
}

void INT0_IRQHander() interrupt 0//外部中断0
{
        Keycontral(Keyscan());
}

//void wrinkle(void)//闪烁
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
