#include<intrins.h>

#define some {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();};

sbit TX = P1^0;
sbit RX = P1^1;

unsigned char code seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};
unsigned char yi,er,san,si,wu,liu,qi,ba;

unsigned char shijian[] = {55,59,23,0,0,0,0};

unsigned char cp,wendu,wenxiaoshu,dianya;
unsigned int juli,t;

bit chao_flag = 0;


void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

void banzi_init()
{
	P2 = 0x80;
	P0 = 0xff;
	
	P2 = 0xa0;
	P0 = 0x00;
	
	P2 = 0xc0;
	P0 = 0xff;
	P2 = 0xff;
	P0 = 0xff;
}

void xianshi()
{
	static unsigned char i = 0;
	switch(i)
	{
		case 0:P2 = 0xc0;P0 = 0x01;P2 = 0xff;P0 = seven_seg[yi];break;
		case 1:P2 = 0xc0;P0 = 0x02;P2 = 0xff;P0 = seven_seg[er];break;
		case 2:P2 = 0xc0;P0 = 0x04;P2 = 0xff;P0 = seven_seg[san];break;
		case 3:P2 = 0xc0;P0 = 0x08;P2 = 0xff;P0 = seven_seg[si];break;
		case 4:P2 = 0xc0;P0 = 0x10;P2 = 0xff;P0 = seven_seg[wu];break;
		case 5:P2 = 0xc0;P0 = 0x20;P2 = 0xff;P0 = seven_seg[liu];break;
		case 6:P2 = 0xc0;P0 = 0x40;P2 = 0xff;P0 = seven_seg[qi];break;
		case 7:P2 = 0xc0;P0 = 0x80;P2 = 0xff;P0 = seven_seg[ba];break;
	}
	i++;
	if(i >= 8)i = 0;
//	P2 = 0xc0;
//	P0 = 0x01;
//	P2 = 0xff;
//	P0 = seven_seg[yi];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x02;
//	P2 = 0xff;
//	P0 = seven_seg[er];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x04;
//	P2 = 0xff;
//	P0 = seven_seg[san];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x08;
//	P2 = 0xff;
//	P0 = seven_seg[si];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x10;
//	P2 = 0xff;
//	P0 = seven_seg[wu];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x20;
//	P2 = 0xff;
//	P0 = seven_seg[liu];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x40;
//	P2 = 0xff;
//	P0 = seven_seg[qi];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x80;
//	P2 = 0xff;
//	P0 = seven_seg[ba];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0xff;
//	P2 = 0xff;
//	P0 = 0xff;
//	Delay1ms();
}

void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xD4;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void timer()interrupt 1
{
	cp++;
	if(cp >= 200)
	{
		cp = 0;
		chao_flag = 1;
	}
	xianshi();
}

void Timer1Init(void)		//2毫秒@11.0592MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
//	TL1 = 0x9A;		//设置定时初值
//	TH1 = 0xA9;		//设置定时初值
//	TF1 = 0;		//清除TF1标志
//	TR1 = 1;		//定时器1开始计时
}


void chaoshengbo()
{
	unsigned char i = 8;
	do
	{
		TX = 1;
		some;some;some;some;some;some;some;some;some;some;
		TX = 0;
		some;some;some;some;some;some;some;some;some;some;
	}while(i--);
}

void ceju()
{
	if(chao_flag == 1)
	{
		chao_flag = 0;
		chaoshengbo();
		TR1 = 1;
		while((RX == 1) && (TF1 == 0));
		TR1 = 0;
		if(TF1 == 1)
		{
			TF1 = 0;
			juli = 999;
		}
		else 
		{
			t = TH1 << 8;
			t |= TL1;
			juli = (unsigned int)(t * 0.017);
			juli = juli / 12;
		}
		TH1 = 0;
		TL1 = 0;
	}
}
