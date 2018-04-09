//1602单色字符液晶显示器，针对教材设计
//通过1602单色液晶显示器
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#include<lcd1602.c>
void main (void)  
{
  	uchar i,sec = 56;
	F1602_init();
  	F1602_clear();
  	while(1)
  	{ 																	//清屏函数
  		F1602_clear();
		display_string("How are you");	
  		gotoxy(2,0);																	//定位第二行
  		display_string("dat:2012/09/01");
  		delay(50000);
		delay(50000);
		delay(50000);
		delay(50000);							//第一屏延时
  		F1602_clear();
  		display_string("Time:");
		display_num(sec);
		display_string("  ");
		display_num(i);		//i为重复显示的次数	
		gotoxy(2,0);
		display_string("End");	
		delay(50000);
		delay(50000);
		delay(50000);
		delay(50000);							//第二屏延时
		i++;if(i > 100)i = 0;
	} 
}
