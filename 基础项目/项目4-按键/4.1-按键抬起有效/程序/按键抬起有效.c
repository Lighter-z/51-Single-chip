#include<reg51.h>
sbit key1 = P2^0;		  //P2.0口接按键
sbit LED = P0^0;		 //P0.0口接LED
void delay(unsigned int x) //延时函数
{
	while(x--);
}
void key()						//按键函数
{
	if(key1==0)					//如果按键按下
	{
		delay(500);        //消抖
		if(key1==0)		  //按键真的按下
		{
			while(key1==0);	   //等待按键抬起
			LED = !LED;		  
		}
	}
}
void main()
{
	P0 = 0x00;		   //让P0.0口全为低电平
	while(1)
	{
		key();		   //调用按键函数
	}
}	
