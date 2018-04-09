#include<reg51.h>
sbit led = P2^0;
void it0_isr()interrupt 0	  //中断服务函数
{
	led = !led;				 
}
void it0_init()			//中断初始化
{
	EA = 1;				//总中断开
	EX0 = 1;			//IT0中断开
	IT0 = 1;		   //TCON中控制INT0触发方式位，INT0下降沿触发中断
}
void main()
{
	it0_init();	   //等待中断
	while(1);
}