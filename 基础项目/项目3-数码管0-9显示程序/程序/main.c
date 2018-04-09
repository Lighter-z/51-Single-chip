#include<reg51.h>
code unsigned char 	seven_seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,
			0x82,0xf8,0x80,0x90};//共阳数码管 0 - 9
unsigned char i = 0;
void delay(unsigned int x)//延时函数
{
	while(x--);
}
void main()
{
	while(1)
	{
		P0 = seven_seg[i];//显示数字
		delay(50000);//延时
		i++;
		if(i>9)i = 0;
	}
}