

#define smoebo {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();};

sbit TX = P1^0;
sbit RX = P1^1;

unsigned char code seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};
unsigned char yi,er,san,si,wu,liu,qi,ba;
unsigned char dianya = 0,cp = 0;
unsigned int juli,t;
unsigned char zaizhong = 0,cp1,cp2,cp3,lei = 0;
unsigned char shijian,shijian_yi,shijian_er,shijian_er_t,shijian_yi_t,shezhi = 0;

bit flag = 0;
bit fengming = 0;
bit huo = 0;
bit yun = 0;
bit tingzhi = 0;

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

void chaoshengbo()
{
	unsigned char i = 8;
	do
	{
		TX = 1;
		smoebo;smoebo;smoebo;smoebo;smoebo;smoebo;smoebo;smoebo;smoebo;smoebo;
		TX = 0;
		smoebo;smoebo;smoebo;smoebo;smoebo;smoebo;smoebo;smoebo;smoebo;smoebo;
	}while(i--);
}

void Timer0Init(void)		//2毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x9A;		//设置定时初值
	TH0 = 0xA9;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
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

void timer0()interrupt 1
{
	cp++;
	cp1++;
	if(cp >= 100)
	{
		cp = 0;
		flag = 1;
	}
	if(cp1 >= 250)
	{
		fengming = !fengming;
		cp1 = 0;
	}
	if((yun == 1) && (tingzhi == 0))
	{
		cp2++;
		if(cp2 > 250)
		{
			cp2 = 0;
			cp3++;
			if(cp3 > 2)
			{
				shijian--;
				if(shijian <= 0)
				{
					shijian = 0;
					yun = 0;
					huo = 0;
				}
			}
		}
	}
}

void ceju()
{
	if(flag == 1)
	{
		flag = 0;
		chaoshengbo();
		TR1 = 1;
		while((TF1 == 0) && (RX == 1));
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
	
	if(yun == 0)
	{
		shijian_yi = IIC_Read(0x01);
		Delay1ms();
		shijian_er = IIC_Read(0x02);
		if(juli <= 30)
		{
			lei = 1;
			shijian = shijian_yi;
		}
		else 
		{
			lei = 2;
			shijian = shijian_er;
		}
	}
}

void banzi_init()
{
	P2 = 0xa0;
	P0 = 0x00;
	
	P2 = 0x80;
	P0 = 0xff;
	
	P2 = 0xc0;
	P0 = 0xff;
	P2 = 0xff;
	P0 = 0xff;
}

void xianshi()
{
	P2 = 0xc0;
	P0 = 0x01;
	P2 = 0xff;
	P0 = seven_seg[yi];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x02;
	P2 = 0xff;
	P0 = seven_seg[er];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x04;
	P2 = 0xff;
	P0 = seven_seg[san];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x08;
	P2 = 0xff;
	P0 = seven_seg[si];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x10;
	P2 = 0xff;
	P0 = seven_seg[wu];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x20;
	P2 = 0xff;
	P0 = seven_seg[liu];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x40;
	P2 = 0xff;
	P0 = seven_seg[qi];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x80;
	P2 = 0xff;
	P0 = seven_seg[ba];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0xff;
	P2 = 0xff;
	P0 = 0xff;
	Delay1ms();
}