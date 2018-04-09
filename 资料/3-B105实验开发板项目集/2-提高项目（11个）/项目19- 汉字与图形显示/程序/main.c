//LCD1286液晶屏显示，针对B105型实验开发板设计
//第一屏显示图片，的二屏显示文字
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include"LCD12864.c"
#include <intrins.h>
void Delay1000ms()						//@11.0592MHz
{
	unsigned char i, j, k;
	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void main(void)
{
   	initinal();
   	gui_clear();
   	Display_Clear();
	xianshi();							//第一屏图片显示
	Delay1000ms();	Delay1000ms();
	gui_clear();
   	while(1)
	{	
		lcd_mesg(1,1,12,"好人一生平安，");
		lcd_mesg(2,1,12,"祝你一帆风顺。");
		lcd_mesg(3,1,9,"123456789");
		lcd_mesg(4,1,12,"abcdefghij");	
	}
}
