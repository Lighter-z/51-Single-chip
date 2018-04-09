//电子表，针对教材设计
//用共阳数码管在P0口、P2口以及74hc04芯片驱动下，显示24小时制电子表 
//电子表程序是利用STC8591内部的定时∕计数器实现精确计数。
//电子表共有四个按键key1、key2、key3、key4分别实现调模式、
//增加、减少、复位功能，其中调模式按键key1可以分别调节小时、分钟、秒钟、闹铃	  
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#include<key.c>
unsigned char i,j,k;
unsigned char seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,
								0x92,0x82,0xf8,0x80,0x90};
unsigned char flash;
sbit SW = P3^3;																		//接继电器驱动电路，低电平继电器吸合，控制电铃
void timer0_isr(void) interrupt 1
{
	TH0 = 0xf8;
	TL0 = 0x2f;
	i++;
	if(i >= 250)																	//半秒时间到
	{
		flash = ~flash;																//得到8位闪烁变量
		i = 0;
		j++;
	}
	if(j >= 2)																		//1分钟到
	{
		sec++;
		j = 0;
	}													
	if(sec >= 60)																	//1分钟到
	{																		
		min++;
		sec = 0;
	}
	if(min >= 60)																	//1小时到
	{											  	
		hour++;
		min = 0;
	}
	if(hour >= 24)   
	hour = 0;
	P0 = 0xff;																		//Protuse软件仿真消隐
	if(key1_flag == 0)																//正常走时
	{
		switch(k)
		{
			case 0:P0 = seven_seg[sec % 10]; P2 = ~0x01;break;
			case 1:P0 = seven_seg[sec / 10]; P2 = ~0x02;break;
		   	case 2:P0 = seven_seg[min % 10] & (0x7f | flash); P2 = ~0x04;break;		//小数点闪烁
		   	case 3:P0 = seven_seg[min / 10]; P2 = ~0x08;break;
		   	case 4:P0 = seven_seg[hour % 10] & (0x7f | flash); P2 = ~0x10;break;	//小数点闪烁
		   	case 5:P0 = seven_seg[hour / 10]; P2 = ~0x20;break;
		}
	}
	if(key1_flag == 1)																//调小时，小时闪烁
	{
		j = 0;
		switch(k)
		{
			case 0: P0 = seven_seg[sec_t % 10]; P2 = ~0x01;break;
			case 1: P0 = seven_seg[sec_t / 10]; P2 = ~0x02;break;
		   	case 2: P0 = seven_seg[min_t % 10]; P2 = ~0x04;break;
		   	case 3: P0 = seven_seg[min_t / 10]; P2 = ~0x08;break;
		   	case 4: P0 = seven_seg[hour_t % 10] | flash; P2 = ~0x10;break;			//小时闪烁
		   	case 5: P0 = seven_seg[hour_t / 10] | flash; P2 = ~0x20;break;			//小时闪烁
		}
	}
	if(key1_flag == 2)																//调分钟
	{
		j = 0;
		switch(k)
		{
			case 0: P0 = seven_seg[sec_t % 10]; P2 = ~0x01;break;
			case 1: P0 = seven_seg[sec_t / 10]; P2 = ~0x02;break;
		   	case 2: P0 = seven_seg[min_t % 10]| flash; P2 = ~0x04;break; 			//分闪烁
		   	case 3: P0 = seven_seg[min_t / 10]| flash; P2 = ~0x08;break;			//分闪烁
		   	case 4: P0 = seven_seg[hour_t % 10] ; P2 = ~0x10;break;
		   	case 5: P0 = seven_seg[hour_t / 10]; P2 = ~0x20;break;
		}
	}	
	if(key1_flag == 3)																//调秒
	{
		j = 0;
		switch(k)
		{
			case 0: P0 = seven_seg[sec_t % 10]| flash; P2 = ~0x01;break;			//秒闪烁
			case 1: P0 = seven_seg[sec_t / 10]| flash; P2 = ~0x02;break;			//秒闪烁
		   	case 2: P0 = seven_seg[min_t % 10]; P2 = ~0x04;break;
		   	case 3: P0 = seven_seg[min_t / 10]; P2 = ~0x08;break;
		   	case 4: P0 = seven_seg[hour_t % 10] ; P2 = ~0x10;break;
		   	case 5: P0 = seven_seg[hour_t / 10]; P2 = ~0x20;break;
		}
	}
	if(key1_flag == 4)																//调定闹小时
	{
		j = 0;
		switch(k)
		{
			case 0: P0 = seven_seg[min_r % 10]; P2 = ~0x01;break;
			case 1: P0 = seven_seg[min_r / 10]; P2 = ~0x02;break;
		   	case 2: P0 = seven_seg[hour_r % 10]| flash; P2 = ~0x04;break;			//定闹小时闪烁
		   	case 3: P0 = seven_seg[hour_r  / 10]| flash; P2 = ~0x08;break;			//定闹小时闪烁
			case 4: P0 = 0xff;P2 = ~0x10;break;										//不显示
			case 5: P0 = 0x0c;P2 = ~0x20;break;										//显示字符"P"
		}
	}
	if(key1_flag == 5)																//调定闹分钟
	{
		j = 0;
		switch(k)
		{
			case 0: P0 = seven_seg[min_r % 10]| flash; P2 = ~0x01;break;			//定闹分闪烁
			case 1: P0 = seven_seg[min_r / 10]| flash; P2 = ~0x02;break;			//定闹分闪烁
		   	case 2: P0 = seven_seg[hour_r % 10]; P2 = ~0x04;break;
		   	case 3: P0 = seven_seg[hour_r  / 10]; P2 = ~0x08;break;
			case 4: P0 = 0xff;P2 = ~0x10;break;										//不显示
			case 5: P0 = 0x0c;P2 = ~0x20;break;										//显示字符"P"
		}
	}
	k++;
	if(k >= 6)k = 0;
}
void timer0_initi(void)																//中断初始化函数
{
	TMOD = 0x01;																	
	TH0 = 0xf8;
	TL0 = 0x2f;																		//每次触发中断后从装初值，使下次对机器脉冲计数2000个计满溢出引发中断  约0.2ms
	EA = 1;																			//开总中断
	TR0 = 1;																		//启动定时器T0
	ET0 = 1;																		//开T0中断
}
void main(void)
{
	timer0_initi();
	while(1)
	{
		key();																		//调用按键函数
		if(min == min_r && hour == hour_r)											//当时间等于闹钟			
		SW = 1;																		//闹铃响起
		else 
		SW = 0;
	}
}
