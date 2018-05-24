#include<stc15f2k60s2.h>
#include<intrins.h>

unsigned char aaa[] = "zm\r\n";
unsigned char zzz[] = "lmz\r\n";
unsigned char num,flag;

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


void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0xE0;		//设定定时初值
	TH1 = 0xFE;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

void Uart() interrupt 4 using 1
{
	RI = 0;
	num = SBUF;
	if(num == 'A')
	{
		P2 = 0x80;
		P0 = 0xfe;
	}
}

void send(unsigned char *p)
{
	unsigned char i = 0;
	do
	{
		SBUF = p[i++];
		while(TI == 0);
		TI = 0;
	}while(p[i] != 0);
}

void key()
{
	if(P30 == 0)
	{
		Delay1ms();
		if(P30 == 0)
		{
			while(P30 == 0);
			send(aaa);
		}
	}
}

void main()
{
	banzi_init();
	UartInit();
	EA = 1;
	ES = 1;
	while(1)
	{
		key();
	}
}	
