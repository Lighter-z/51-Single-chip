//DA转换器TLC5615应用，针对教材设计
//DA转换器TLC5615可以将数字信号（即电压变化信号）转换为模拟信号（即连续的模拟数据）
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#include<TLC5615.c>
#define uchar unsigned char										//宏定义 即用uchar 代替unsigned char 
#define uint unsigned int										//宏定义 即用uint 代替unsigned int
sbit P1_0 = P1^0;
uchar j;
uint moni,dat,i; 
code uchar seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,
							0x92,0x82,0xf8,0x80,0x90};			//共阳极数码管0~9显示数组
/* **************T0初始化函数*****************/
void timer0_init(void)									
{
	TMOD = 0x01;
	TL0 = (65536-2000) % 256;
	TH0 = (65536-2000) / 256;
	TR0 = 1;
	ET0 = 1;
	EA  = 1;
}
/*********** T0中断服务函数*******************/
void timer0_isr() interrupt 1									//T0的中断处理函数，用于显示输出的电压值
{
	TL0 = (65536-2000) % 256;
	TH0 = (65536-2000) / 256;
	i++;
	if(i >= 500)//0.5秒
	{	
		i = 0;	
		tlc5615(dat);
		if(dat >= 962)
		dat = 0;
		moni = dat * 0.489;
		dat = dat + 10;
	}
	P0 = 0xff;
	switch(j)
	{
		case 0 : P0 = seven_seg[moni %10];P2 = 0xfe;break;
		case 1 : P0 = seven_seg[moni / 10 % 10];P2 = 0xfd;break;
		case 2 : P0 = seven_seg[moni / 100] & 0x7f;P2 = 0xfb;break;		
	}
	j++;
	if(j >= 3)
	j = 0;
}
/* *****************主函数********************/
void main()
{
	timer0_init();
	while(1);
}
