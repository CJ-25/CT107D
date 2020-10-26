# CT107D
蓝桥杯单片机

#include "STC15F2K60S2.h"
#include	"iic.h" 
#define uchar unsigned char
#define uint unsigned int
uchar code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff};		//段码表
uchar yi,er,san,si,wu,liu,qi,ba;
void diaplay1(uchar yi,uchar er,uchar san,uchar si);
void diaplay2(uchar wu,uchar liu,uchar qi,uchar ba);
void keyscan();
void Timer1Init(void)	;
void allinit();
void delayms(int xms);
uchar temp=0xff,key=0xff;
uint tt,shuiliang=0,price=0;
uchar ad;

void main()
{
		allinit();
		Timer1Init();
		yi=10;er=0;san=5;si=0;wu=0;liu=1;qi=0;ba=0;
	while(1)
	{
			keyscan();
		ad=readad(0x01);
		ad=ad*0.019;
		if(ad<1.25)
		{
				P2=((P2&0X1F)|0X80);P0=0XFE;P2&=0X1F;
		}
		else if(ad>1.25)
		{
				P2=((P2&0X1F)|0X80);P0=0XFf;P2&=0X1F;
		}		
		
		if(shuiliang==10000)
		{
			EA=0;ET1=0;
			price=shuiliang/2; //将得出的水量赋给价钱
			wu=price/1000;		
			liu=price/100%10;
			qi=price/10%10;
			ba=price%10;
			shuiliang=0;
			P2=((P2&0X1F)|0XA0);P0=0X00;P2&=0X1F;
		}
	
		 diaplay1( yi, er, san, si);
		 diaplay2( wu, liu, qi, ba);
	}
}

void keyscan()
{

	temp=P3;
	if((temp&0x0f)!=0x0f)
		{
			delayms(5);
			temp=P3;
			if((temp&0x0f)!=0x0f)
			{
				key=temp&0x0f;
				
			}
		}
	if(((key&0x0f)!=0x0f)&&((temp&0x0f)==0x0f))
		{
			delayms(5);
			if((temp&0x0f)==0x0f)
			{
				switch(key)
				{
					case 0x0e:
										EA=1;ET1=1;
										P2=((P2&0X1F)|0XA0);P0=0X10;P2&=0X1F;
										key=0xff;break;
					case 0x0d:
										EA=0;ET1=0;
										price=shuiliang/2;
										wu=price/1000;		
										liu=price/100%10;
										qi=price/10%10;
										ba=price%10;
										P2=((P2&0X1F)|0XA0);P0=0X00;P2&=0X1F;
										shuiliang=0;  
										key=0xff;break;					
				}
			}
		}		
}

void timer1() interrupt 3
{
	tt++;
	if(tt==1000)
	{
		tt=0;
		shuiliang=shuiliang+10;
		wu=shuiliang/1000;		
		liu=shuiliang/100%10;
		qi=shuiliang/10%10;
		ba=shuiliang%10;
	}
}

void Timer1Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xCD;		//设置定时初值
	TH1 = 0xD4;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
}


void diaplay1(uchar yi,uchar er,uchar san,uchar si)
{
	P2=((P2&0X1F)|0XE0);P0=0XFF;P2&=0X1F;
	P2=((P2&0X1F)|0XC0);P0=0x01;P2&=0X1F;
	P2=((P2&0X1F)|0XE0);P0=tab[yi];P2&=0X1F;
	delayms(1);
	P2=((P2&0X1F)|0XC0);P0=0x02;P2&=0X1F;
	P2=((P2&0X1F)|0XE0);P0=tab[er]&0x7f;P2&=0X1F;
	delayms(1);
	P2=((P2&0X1F)|0XC0);P0=0x04;P2&=0X1F;
	P2=((P2&0X1F)|0XE0);P0=tab[san];P2&=0X1F;
	delayms(1);
	P2=((P2&0X1F)|0XC0);P0=0x08;P2&=0X1F;
	P2=((P2&0X1F)|0XE0);P0=tab[si];P2&=0X1F;
	delayms(1);
	
}
void diaplay2(uchar wu,uchar liu,uchar qi,uchar ba)
{
	P2=((P2&0X1F)|0XE0);P0=0XFF;P2&=0X1F;
	P2=((P2&0X1F)|0XC0);P0=0x10;P2&=0X1F;
	P2=((P2&0X1F)|0XE0);P0=tab[wu];P2&=0X1F;
	delayms(1);
	P2=((P2&0X1F)|0XC0);P0=0x20;P2&=0X1F;
	P2=((P2&0X1F)|0XE0);P0=tab[liu]&0x7f;P2&=0X1F;
	delayms(1);
	P2=((P2&0X1F)|0XC0);P0=0x40;P2&=0X1F;
	P2=((P2&0X1F)|0XE0);P0=tab[qi];P2&=0X1F;
	delayms(1);
	P2=((P2&0X1F)|0XC0);P0=0x80;P2&=0X1F;
	P2=((P2&0X1F)|0XE0);P0=tab[ba];P2&=0X1F;
	delayms(1);
	P2=((P2&0X1F)|0XC0);P0=0xff;P2&=0X1F;
	P2=((P2&0X1F)|0XE0);P0=0xff;P2&=0X1F;
	delayms(1);
}

void allinit()
{
	P2=((P2&0X1F)|0XA0);P0=0X00;P2&=0X1F;
	P2=((P2&0X1F)|0X80);P0=0XFF;P2&=0X1F;
	P2=((P2&0X1F)|0XC0);P0=0XFF;P2&=0X1F;
	P2=((P2&0X1F)|0XE0);P0=0XFF;P2&=0X1F;
}

void delayms(int xms)  //延时函数
{
	int i,j;
	for(i=xms;i>0;i--)
	for(j=845;j>0;j--);
}


