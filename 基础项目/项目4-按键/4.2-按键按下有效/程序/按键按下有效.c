#include<reg51.h>
sbit key1 = P2^0;		  //P2.0口接按键
sbit led = P0^0;		 //P0.0口接LED
void delay(unsigned int x) //延时函数
{
	while(x--);
}
void key()
{
	if(key1==0)			 //如果按键按下
	{
		delay(500);		    //消抖
		if(key1==0)	       //如果真的按下
		{
		led=!led;		   
		delay(5000);	  //延时
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
