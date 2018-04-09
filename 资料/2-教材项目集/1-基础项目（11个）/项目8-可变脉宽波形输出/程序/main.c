//可变脉宽波形输出，针对B105型实验开发板设计
//定一个周期，自动调整脉宽
//设计：单片机创新工作室--许敬东设计 ，2015年12月15日
#include<reg51.h>
sbit P1_7 = P1^7;
unsigned char cp1,cp2,tt;
void timer0_init(void)									//中断初试化函数
{
	TMOD = 0x02;										//T0工作方式2
	TL0 = 156;						
	TH0 = 156;											//给定时器赋值
	EA = 1;												//开总中断
	ET0  = 1;											//开T0中断
	TR0 = 1;											//启动定时器T0
}
void timer0_isr(void) interrupt 1						//中断服务函数
{
	cp1++;cp2++;										//设置局部变量
	if(cp1++ >= tt)P1_7 = 1;
	if(cp1++ >= 20){P1_7 = 0;cp1 = 0;}
	if(cp2 >= 255){cp2 = 0;tt++;if(tt >= 20) tt = 0;}
}
void main()
{
	timer0_init();										//中断初始化
	while(1);
}