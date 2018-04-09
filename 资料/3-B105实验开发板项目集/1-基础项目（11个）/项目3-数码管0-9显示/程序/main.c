//单个数码管0-9显示
//单个共阳数码管在P0口以及74hc573芯片驱动下，循环显示0-9
//河南科技学院-单片机协会，2016年10月9日		 
#include<reg51.h>
sbit P3_0 = P3^0;
unsigned char cp;
code unsigned char seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};//数字0~9的显示方法
void delay(unsigned int x)
{
	while(x--);
}
void main(void)
{
	P0 = 0x01;
	P3_0 = 0;P3_0 = 1;P3_0 = 0;//P3.0输出上升沿，使74HC573锁存,	Q0输出高电平； 
	while(1)			
	{	
		P0 = seven_seg[cp];
		delay(50000);
		cp++;				//cp每次加1
		if(cp >= 10)cp = 0;	//到10清零	
	}
}