#include<stc15f2k60s2.h>
#include<intrins.h>

unsigned char code seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char yi,er,san,si,wu,liu,qi,ba;

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

void keyscan()
{
	unsigned char temp;
	P3 = 0x7f;P42 = 0;
	temp = P3;
	temp &= 0x0f;
	if(temp != 0x0f)
	{
		Delay1ms();
		temp = P3;
		temp &= 0x0f;
		if(temp != 0x0f)
		{
			temp = P3;
			switch(temp)
			{
				case 0x7e:yi = 1;break;
				case 0x7d:yi = 2;break;
				case 0x7b:yi = 3;break;
				case 0x77:yi = 4;break;
			}
		}
		while(temp != 0x0f)
		{
			temp = P3;
			temp &= 0x0f;
		}
	}
	P42 = 1;P3 = 0xbf;P42 = 0;
	temp = P3;temp &= 0x0f;
	if(temp != 0x0f)
	{
		Delay1ms();
		temp = P3;temp &= 0x0f;
		if(temp != 0x0f)
		{
			temp = P3;
			switch(temp)
			{
				case 0xbe:er = 1;break;
				case 0xbd:er = 2;break;
				case 0xbb:er = 3;break;
				case 0xb7:er = 4;break;
			}
		}
		while(temp != 0x0f)
		{
			temp = P3;
			temp &= 0x0f;
		}
	}
	P42 = 1;P3 = 0xdf;
	temp = P3;temp &= 0x0f;
	if(temp != 0x0f)
	{
		Delay1ms();
		temp = P3;temp &= 0x0f;
		if(temp != 0x0f)
		{
			temp = P3;
			switch(temp)
			{
				case 0xde:san = 1;break;
				case 0xdd:san = 2;break;
				case 0xdb:san = 3;break;
				case 0xd7:san = 4;break;
			}
		}
		while(temp != 0x0f)
		{
			temp = P3;
			temp &= 0x0f;
		}
	}
}

void main()
{
	banzi_init();
	while(1)
	{
		xianshi();
		keyscan();
	}
}
