//P0.0口驱动LED灯闪烁
//LED在P0.0端口驱动下闪烁
//河南科技学院-单片机协会，2016年10月9日		 
#include<reg51.h>		  			 	//包含51头文件
sbit LED = P0^0;							//定义LED接P0.0
void delay(unsigned int x)		//延时函数
{
	while(x--);
}
void main(void)								//主函数
{
	P0 = 0X00;									//复位后让P0为低电平
	while(1) 
	{	
		P1 = 0;										//关闭74hc573
		LED = 1;									//P0.0输出高电平，LED1亮
		delay(50000);							//调用延时函数，延时一段时间
		LED = 0;									//P0.0输出低电平，LED1灭
		delay(50000);
	}
}
