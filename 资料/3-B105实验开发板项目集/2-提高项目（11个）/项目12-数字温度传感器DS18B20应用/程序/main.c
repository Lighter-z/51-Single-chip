//数字温度传感器应用，教材和B105型实验开发板通用
//实时读取并且显示温度
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#include<ds18b20.c>	
	
code  uchar seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};			//共阳极数码管数显编码
uchar cp1;
uint cp;
sbit P3_0 = P3^0;													//temp_num、temp_num1为温度整数部分，temp_dot小数部分，中间变量temp
void timer0_init(void)																	//中断服务函数	 
{
	TMOD = 0x01;
	TH0 = (65536 - 2000) / 256;
	TL0 = (65536 - 2000) % 256;
	TR0 = 1;
	EA  = 1;
	ET0 = 1;
}
void timer0_isr(void) interrupt 1														//中断服务函数		  	
{
	TH0 = (65536 - 2000) / 256;
	TL0 = (65536 - 2000) % 256;
	cp++;
	P0 = 0xff;
	switch(cp1)
	{
		case 0:P3_0 = 0;P0 = 0x01;P3_0  = 1;P3_0 = 0;
		P0 = seven_seg[c];break;
		case 1:P3_0 = 0;P0 = 0x02;P3_0  = 1;P3_0 = 0;
		P0 = seven_seg[t % 10] & 0x7f;break;
		case 2:P3_0 = 0;P0 = 0x04;P3_0  = 1;P3_0 = 0;
		P0 = seven_seg[t / 10];break;
	}
	cp1++;if(cp1 >= 3)cp1 = 0;
}
void main(void)	
{
	timer0_init();																//向18B20的rom中写数据		
	while(1)
	{
	 	if(cp >= 500)
		{
			cp = 0;
			Read_Temperature();
			c = c * 0.625;
		}	
	}
}
