//数码管显示0-9秒
//数码管按秒显示0-9
//河南科技学院-单片机协会，2016年10月9日		 
#include<reg51.h>
unsigned char cp,sec;
sbit P3_0 = P3^0;
code unsigned char seven_seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};	//数字0~9的显示方法
void timer0_isr()interrupt 1	//中断服务函数
{
	TH0 = (65536-5000)/256;		//每次触发中断后重装初值，8051单片机的T0工作在方式1不能自动重装初值
	TL0 = (65536-5000)%256;
	cp++;						//每次中断cp加1
	if(cp >= 200)				//中断200次，1秒
	{
		cp = 0;					//cp复位
		sec++;
		if(sec >= 10)sec = 0;
	}
	P0 = 0xff;
	P3_0 = 0;P0 = 0x01;P3_0 = 1;P3_0 = 0;//P3.0端口上升沿允许74HC573存储
	P0 = seven_seg[sec];	//显示秒	
}
void timer0_init()			//中断初始化函数
{
	TMOD = 0X01;			//T0工作方式1
	TH0 = (65536-5000)/256;					
	TL0 = (65536-5000)%256;	//对机器脉冲计数5000个计满溢出引发中断，5ms中断1次
	EA = 1;					//开总中断
	ET0 = 1;				//开T0中断
	TR0 = 1;				//启动定时器T0
}
void main()
{	
	timer0_init();			//中断初始化
	while(1);
} 