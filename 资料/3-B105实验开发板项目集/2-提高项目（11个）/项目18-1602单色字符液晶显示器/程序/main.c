//LCD1602液晶屏应用，针对B105开发板设计
//LCD1602可以显示两行字符，每行最多可以显示16个字符
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#include<74hc595.c>
#include<lcd1602.c>
#define uchar unsigned char
#define uint unsigned int
/*******************主函数*******************/
void main (void)  
{
	FLCD1602_init();
  	FLCD1602_clear();
  	while(1)
  	{ 	
		gotoxy(1,0);											//从第一行第一位开始显示
  		display_string("How are you");							//第一行显示“How are you”字样
  		gotoxy(2,0);											//从第二行第一位开始显示
  		display_string("dat:2012/09/01");						//第二行显示“dat：2012/09/01”
  		delay(50000);delay(50000);delay(50000);delay(50000);	
	} 
}