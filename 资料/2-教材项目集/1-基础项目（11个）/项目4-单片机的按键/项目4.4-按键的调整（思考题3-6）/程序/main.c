//利用按键调整数码管的数值，针对教材设计
//两个按键，分别控制加和减
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#include<key.c>
sbit P1_0 = P1^0;
unsigned char k;
code unsigned char seven_seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void display()				//显示函数
{
	P0 = 0xff;
	switch(k)
	{
		case 0:P0 = 0x01;P1_0 = 0;P1_0 = 1;P1_0 = 0;P0 = seven_seg[i % 10];break;
		case 1:P0 = 0x02;P1_0 = 0;P1_0 = 1;P1_0 = 0;P0 = seven_seg[i / 10];break;
	}
	k++;
	if(k > 1) k = 0;
}
void main()
{
	while(1)
	{
		key_scan();			//调用按键函数
		display();			//调用显示函数
		delay(300);			
	}
}