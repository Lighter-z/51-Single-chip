#include<reg51.h>
sbit LED = P0^0;		  //LED接P0.0
void delay(unsigned int x)			 //延时函数
{
	while(x--);
}
void main()							 //主函数
{
	while(1)
	{
	LED=0;									  //P0.0输出低电平，LED灭
	delay(5000);							 //调用延时函数，延时一段时间
	LED=1;									//P0.0输出高电平，LED亮
	delay(5000);						   //调用延时函数，延时一段时间
	}
}  
