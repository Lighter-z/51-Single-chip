//PCF8591应用，教材和B105型实验开发板通用
//DA转换
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#include<PCF8591.c>
code uchar seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,
							0x92,0x82,0xf8,0x80,0x90};			//共阳极数码管0~9显示数组
uchar cp1,cp2,cp3;
sbit P1_0 = P1^0;
uint sec,temp,temp1;	
void display(void)
{	                                            
	switch(cp3)
	{
		case 0: P0 = 0xff; 										//消隐，只在软件仿真中用到
				P1_0 = 0;P0 = 0x01;P1_0 = 1;P1_0 = 0;
				P0 = seven_seg[sec % 10]; break;
		case 1: P0 = 0xff;
				P1_0 = 0;P0 = 0x02;P1_0 = 1;P1_0 = 0;
				P0 = seven_seg[sec / 10 % 10]; break;
		case 2:	P0 = 0xff;
				P1_0 = 0;P0 = 0x04;P1_0 = 1;P1_0 = 0;
				P0 = seven_seg[sec / 100]& 0x7f; break;	
		case 3: P0 = 0xff;
				P1_0 = 0;P0 = 0x08;P1_0 = 1;P1_0 = 0;
				P0 = 0xbf;break; 
		case 4: P0 = 0xff;
				P1_0 = 0;P0 = 0x10;P1_0 = 1;P1_0 = 0;
				P0 = 0xbf;break;
		case 5:	P0 = 0xff;
				P1_0 = 0;P0 = 0x20;P1_0 = 1;P1_0 = 0;
		 	   	P0 = 0xbf;break; 
		case 6: P0 = 0xff;		 
				P1_0 = 0;P0 = 0x40;P1_0 = 1;P1_0 = 0;
				P0 = 0xbf;break;
		case 7: P0 = 0xff;
				P1_0 = 0;P0 = 0x80;P1_0 = 1;P1_0 = 0;
				P0 = 0xbf;
				break;
	}
	cp3++;
	if(cp3 >= 8)cp3 = 0;
}			   
void timer0_isr(void) interrupt 1
{	
	TH0 = (65536 - 2000) / 256;									//重装初值
	TL0 = (65536 - 2000) % 256;									//重装初值
	cp1++;														//中断1次，变量加1
	if(cp1 >=  250)												//半秒到了	 
	{
		cp1 = 0;
		temp = temp + 10;
		if(temp >= 256)
		temp = 0;
		sec = temp*1.91;	
		DA_PCF8591(0x40,temp);									// 表示四路单数入00通道无增益的器件控制指令		DA数据
	}
	display();
}
void timer0_init(void)
{
	TMOD = 0x01;												//T0工作方式1
	TH0 = (65536 - 2000) / 256;									//对机器脉冲计数2000个计满溢出引发中断
	TL0 = (65536 - 2000) % 256;
	EA = 1;														//开总中断
	ET0 = 1;													//开T0中断
	TR0 = 1;													//启动定时器T0
}
void main(void)													//主函数
{
	timer0_init();
	while(1);													//等待中断  
}