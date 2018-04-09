//电子表设计
//利用4个按键调整时间
//具有定闹功能
//设计者，河南科技学院单片机协会，2016年10月
#include<reg51.h>
#include<display.c>
#include<key.c>
unsigned int cp1;
unsigned char cp2;
sbit P1_2 = P1^2;
void timer0_isr(void) interrupt 1
{
	TH0 = (65536 - 1000) / 256;
	TL0 = (65536 - 1000) % 256;
	cp1++;
	if(cp1  >= 500)
	{
		cp1 = 0;
		flash = ~flash;
		cp2++;
	}
	if(cp2 >= 2)
	{
		cp2 = 0;
		sec++;
		if(sec >= 60){sec = 0;min++;}
		if(min >= 60){min = 0;hour++;}
		if(hour >= 24)hour = 0;
	}
	P0 = 0xff;
	switch(mode)
	{
		case 0:dis_play0();break;
		case 1:dis_play1();break;
		case 2:dis_play2();break;
		case 3:dis_play3();break;
		case 4:dis_play4();break;
		case 5:dis_play5();break;
	}
	cp3++;
	if(cp3 >= 8)cp3 = 0;
}
void timer0_init(void)
{
	TMOD = 0x01;
	TH0 = (65536 - 1000) / 256;
	TL0 = (65536 - 1000) % 256;
	EA = 1;
	ET0 = 1;
	TR0 =1;
}
void main(void)
{
	timer0_init();
	while(1)
	{
		key();
		if(hour == hour_n && min == min_n)P1_2 = 0;
		else P1_2 = 1;							
	}
}