//用单片机P3.2端口控制LED灯闪烁，针对教材设计
//按键按下，LED改变状态
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
sbit key1 = P3^2;					      //定义key1为P3.2端口
sbit LED = P0^0;					      //定义LED为P0.0端口
void delay(unsigned int x)
{
	while(x--);
}
void key(void)					          //按键函数
{
	if(key1 == 0)					      //检测P3.2端口是否为低电平
	{
		delay(500);						  //延时一段时间，达到消抖的目的
		if(key1 == 0)					  //再次判断按键是否按下
		{
			LED = !LED;				      //如果按下，使P0.0端口取反
			delay(50000);				  //防止LED闪烁太快
		}
	}	
}
void main(void)
{
	P0 = 0x00;							  //让LED全灭
	while(1)
	{
		key();							  //调用按键函数
	}
}