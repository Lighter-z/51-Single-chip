//P0.0口驱动LED灯闪烁，教材和B105型实验开发板通用
//LED在P0.0端口驱动下闪烁
//设计：单片机创新工作室--冷恩鑫设计，2015年12月15日		 
#include<reg51.h>		  			 	//包含51头文件
sbit LED = P0^0;						//定义LED接P0.0
void delay(unsigned int x)		     	//延时函数
{
	while(x--);
}
void main(void)							//主函数
{
	P0 = 0X00;
					    	//复位后让P0为低电平
	while(1) 
	{
		LED = 1;						//P0.0输出高电平，LED1亮
		delay(10);					//调用延时函数，延时一段时间
		LED = 0;						//P0.0输出低电平，LED1灭
		delay(2);
	}
}
