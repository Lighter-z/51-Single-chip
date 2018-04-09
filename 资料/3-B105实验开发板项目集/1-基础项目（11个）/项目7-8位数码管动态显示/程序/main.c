//8位数码管动态显示
//用8位共阳数码管在P0口以及74HC573芯片驱动下，显示0-7
//河南科技学院-单片机协会，2016年10月9日		 
#include<reg51.h>
sbit P3_0 = P3^0;
code unsigned char seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,
									0x82,0xf8,0x80,0x90,0xbf,0xff};	//数字0~9的显示方法 
unsigned int cp;
unsigned char tp,sec = 30,min = 30,hour = 12; 						 

void timer0_isr(void) interrupt 1	//中断服务函数
{
	TH0 = (65535 - 2000) / 256;		//每次触发中断后从装初值，使下次对机器脉冲计数2000个计满溢出引发中断  约0.2ms
	TL0 = (65535 - 2000) % 256;
	cp++;
	if(cp >= 500)
	{
		cp = 0;
		sec++;
		if(sec >= 60){sec = 0;min++;}
		if(min >= 60){min = 0;hour++;}
		if(hour >= 24)hour = 0;
	}
	P0 = 0xff;
	switch(tp)
	{
		case 0:P3_0 = 0;P0 = 0x01;P3_0 = 1;P3_0 = 0;P0 = seven_seg[sec % 10];break;	
		case 1:P3_0 = 0;P0 = 0x02;P3_0 = 1;P3_0 = 0;P0 = seven_seg[sec / 10];break;	
		case 2:P3_0 = 0;P0 = 0x04;P3_0 = 1;P3_0 = 0;P0 = 0xbf;break;	
		case 3:P3_0 = 0;P0 = 0x08;P3_0 = 1;P3_0 = 0;P0 = seven_seg[min % 10];break;		
		case 4:P3_0 = 0;P0 = 0x10;P3_0 = 1;P3_0 = 0;P0 = seven_seg[min / 10];break;	
		case 5:P3_0 = 0;P0 = 0x20;P3_0 = 1;P3_0 = 0;P0 = 0xbf;break;	
		case 6:P3_0 = 0;P0 = 0x40;P3_0 = 1;P3_0 = 0;P0 = seven_seg[hour % 10];break;		
		case 7:P3_0 = 0;P0 = 0x80;P3_0 = 1;P3_0 = 0;P0 = seven_seg[hour / 10];break;	
	}
	tp++;if(tp >= 8)tp = 0;
}
void timer0_init(void)				//中断初始化函数
{
	TMOD = 0x01;				//T0工作方式1
	TH0 = (65535 - 2000) / 256;		//对机器脉冲计数2000个计满溢出引发中断  约0.2ms
	TL0 = (65535 - 2000) % 256;
	EA = 1;						//开总中断
	ET0 = 1;					//开T0中断	
	TR0 = 1;					//启动定时器T0
}
void main(void)
{	
	timer0_init();				//中断初始化
	while(1);
} 