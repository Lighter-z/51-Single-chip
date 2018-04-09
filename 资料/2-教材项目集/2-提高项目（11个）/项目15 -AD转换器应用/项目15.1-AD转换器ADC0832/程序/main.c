//AD转换器ADC0832应用，针对教材设计
/*
   调节电位器R1可以产生一个模拟的0~5V电压源，输入ADC0832的CH0·端口，

   ADC0832转换后的数据范围为0~255，由三位数码管输出。ADC0832的DI

   与DO线与后接单片机的P3.2口，/CS接P3.0口，CLK接P3.1口。为了得到

   CH0通道转换得到的数据，程序中需要在CLK第2、3个下降沿来到时向DI

   发送1、0，然后才能接收ADC0832的转换数据，每次转换结束时让/CS 无效。
*/
//实时读取ADC0832检测电压数据并显示
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#include<intrins.h>
#include"ADC0832.c"
#define uchar unsigned char										//把 unsigned char 宏定义为 uchar
code  uchar seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,
							0x92,0x82,0xf8,0x80,0x90};			//数字0~9的显示方法
uchar cp1,cp2,dat_ad;
void timer0_init(void)											// timer0中断初始化函数
{
	TMOD = 0x01;
	TH0 = 0xec;
	TL0 = 0x78;
	TR0 = 1;
	EA  = 1;
	ET0 = 1;
}
void timer0_isr(void) interrupt 1								// timer0中断服务函数
{
	TH0 = 0xec;
	TL0 = 0x78;
	cp1++;
	if(cp1 >= 100)												//0.5秒
   	{
			cp1 = 0;
			dat_ad = dac0832_ch0();								//0.5秒让ADC0832转换一次
		}
		P0 = 0xff;
		switch(cp2)
		{
			case 0:P0 = seven_seg[dat_ad  % 10];P2 = ~0x01;break;
			case 1:P0 = seven_seg[dat_ad % 100 / 10];P2 = ~0x02;break;
			case 2:P0 = seven_seg[dat_ad / 100];P2 = ~0x04;break;
		}
		cp2++;
		if(cp2 >= 3)
		cp2 = 0;
}
void main(void)													//主函数 
{
		timer0_init();
		dac0832_init();	
		while(1);
}
