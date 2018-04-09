//15单片机内部AD使用，针对B105型实验开发板设计
//模拟信号采用实验板电位器VR1(接P1.1)产生一个0-5V电压
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#include<display.c>
#include<15fad.c>
unsigned int cp1;

void timer0_isr(void) interrupt 1
{
	TH0 =  (65536 - 1000) / 256;
	TL0 =  (65536 - 1000) % 256;
	cp1++;
	P0 = 0xff;
	display();
	cp2++;
	if(cp2 >= 8)cp2 = 0;		
}
void timer0_init(void)
{
	TMOD = 0x01;
	TH0 =  (65536 - 1000) / 256;
	TL0 =  (65536 - 1000) % 256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}
void main(void)
{
	timer0_init();
	while(1)
	{
		if(cp1 >= 500)//半秒
		{
			cp1 = 0;
			ad_dat =  get_ad();//半秒得到一个转换后的数据，然后去显示
		}
	}
}