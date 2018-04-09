#include<reg51.h>
sbit key1 = P3^4;
code unsigned char seven_seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void delay(unsigned int x)	 //延时函数
{
	while(x--);
}
void key()		 //按键函数，抬起有效
{
	unsigned char i;
	if(key1==0)						   //按键按下
	{
		delay(300);					   //消抖
		if(key1==0)							 //真的按下
		{
			while(key1==0) ;			//等待抬起
			P0=seven_seg[i]; 			//从数组中选择数据
			i++;						
			if(i>=10)i=0;
		}
	}
}
void main()
{
	P2=0x00;					//反相器取反
	while(1)
	{
		key();					
	}
}