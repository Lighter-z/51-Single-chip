//学习PWM波的占空比设定,针对B105型实验开发板设计
//15F单片机内部有3个PWM模块，利用编程的方法可以改变,利用模块0产生一个PWM波，从P1.1输出接示波器观察；
//设计：单片机创新工作室--冷恩鑫设计，2015年12月15日
#include<reg51.h>
#include<15fpwm.c>
unsigned char cp1,cp2,pwm_num;
xdata pwm_s;//占空比,占空间16位
void timer0_isr(void) interrupt 1
{
	TH0 =  (65536 - 1000) / 256;
	TL0 =  (65536 - 1000) % 256;
	cp1++;
	if(cp1 >= 100)//0.1毫秒
	{
		pwm_num++;
		if(pwm_num >= 256)pwm_num = 0;
		cp1 = 0;
	}		
}
void timer0_init(void)
{
	TMOD = 0x01;
	TH0 =  (65536 - 1000) / 256;
	TL0 =  (65536 - 1000) % 256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}
void main(void)
{
	timer0_init();
	STC_pwm_init();
	while(1)
	{
		if(CL >= 0xfe)//PC计数器将要计满立即改变CCAP0H值,来改变脉宽
		{
			CCAP0H =  pwm_num;			//P1.1输出
			//CCAP1H =  pwm_num; 		//P1.0输出
			//CCAP2H =  255- pwm_num;	//P3.7输出
		}
	}
}