//外部中断应用
//利用一个按键产生下降沿，触发单片机的外部中断INT0
//河南科技学院-单片机协会，2016年10月9日		 
#include<reg51.h>
sbit LED = P0^0;
void int0_isr(void) interrupt 0	//INT0中断服务函数
{
	LED = !LED;
}
void int0_init(void) //INT0中断初始化
{
	IT0 = 1;
	EA = 1;
	EX0 = 1;
}

void main()
{
	int0_init();	//INT0中断初始化
	while(1);
}