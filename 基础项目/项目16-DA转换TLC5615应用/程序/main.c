#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
#include<TLC5615.c>
uchar cp1,cp2;
uint moni,dat;
void timer0_init(void)
{
	TMOD = 0x01;
	TL0 = (65536 - 2000) % 256;
	TH0 = (65536 - 2000) / 256;
	EA = 1;
	TR0 = 1;
	ET0 = 1;
}
void timer0_isr()interrupt 1
{
	TL0 = (65536 - 2000) % 256;
	TH0 = (65536 - 2000) / 256;
	cp1++;
	if(cp1 >= 500)
	{
		cp1 = 0;
		tlc5615(dat);
		if(dat >= 962)
		dat = 0;
		moni = dat * 0.489;
		dat = dat + 10;	
	}	
	P0 = 0xff;
	switch(cp2)
	{
		case 0: P0 = seven_seg[moni % 10];P2 = 0xfe;break;
		case 1: P0 = seven_seg[moni / 10 % 10];P2 = 0xfd;break;
		case 2: P0 = seven_seg[moni / 100] & 0x7f;P2 = 0xfb;break;
	}
	cp2++;
	if(cp2 >= 3)
	cp2 = 0;
}
void main(void)
{
	timer0_init();
	while(1);
}