//8位数码管动态显示，针对教材设计
//用8位共阳数码管在P0口以及74hc573芯片驱动下，显示0-7
//设计：单片机创新工作室--齐霄涵设计，2015年12月15日
#include<reg51.h>
code unsigned char seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,
									0x82,0xf8,0x80,0x90,0xbf,0xff}; 
unsigned char t;						 
void timer0_isr()interrupt 1						//中断服务函数
{
	TH0 = (65536-2000)/256;							//每次触发中断后从装初值，使下次对机器脉冲计数2000个计满溢出引发中断  约0.2ms
	TL0 = (65536-2000)%256;
    P0 = 0xff;										//Proteus 仿真需要消隐
	switch(t)
	{
		case 0:P0 = seven_seg[0];P2 = ~0x01;break;	//数码管段选，数码管位选
		case 1:P0 = seven_seg[1];P2 = ~0x02;break;
		case 2:P0 = seven_seg[2];P2 = ~0x04;break;
		case 3:P0 = seven_seg[3];P2 = ~0x08;break;
		case 4:P0 = seven_seg[4];P2 = ~0x10;break;
		case 5:P0 = seven_seg[5];P2 = ~0x20;break;
		case 6:P0 = seven_seg[6];P2 = ~0x40;break;
		case 7:P0 = seven_seg[7];P2 = ~0x80;break;
	}
	t++;if(t>=8)t=0;
}
void timer0_init()									//中断初始化函数
{
	TMOD = 0X01;									//T0工作方式1
	TH0 = (65536-2000)/256;							//对机器脉冲计数2000个计满溢出引发中断  约0.2ms
	TL0 = (65536-2000)%256;
	EA = 1;											//开总中断
	TR0 = 1;										//启动定时器T0
	ET0 = 1;										//开T0中断
}
void main()
{	
	timer0_init();									//中断初始化
	while(1);
} 