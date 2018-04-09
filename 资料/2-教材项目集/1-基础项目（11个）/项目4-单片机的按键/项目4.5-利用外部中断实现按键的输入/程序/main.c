//外部中断控制LED闪烁，针对教材设计
//按键按下，P3.2端口下降沿触发中断，LED状态改变
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
sbit LED = P0^0;
void timer0_isr()interrupt 0
{
	LED = !LED;
}
void timer0_init()		//中断初始化
{
	IT0 = 1;			//TCON中控制INT0触发方式位，INT0下降沿触发中断
	EA = 1;  			//总中断允许
	EX0 = 1;			//中断允许
}
void main()
{
	P0 = 0x00;			//让LED全灭
	timer0_init();		
	while(1);		   	//等待中断
}