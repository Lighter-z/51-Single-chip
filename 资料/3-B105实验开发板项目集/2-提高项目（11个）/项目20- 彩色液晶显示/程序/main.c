//彩色液晶显示，针对105型实验开发板设计
//通过彩色液晶显示彩色图片，使用单片机为15F系列单片机
//设计：单片机创新工作室--冷恩鑫设计，2015年12月15日
#include <reg51.h>
#include <intrins.h>
#include<tupian.c>
#include<TFT.c>
void main(void)
{  
    P2 = 0xff;
    P0 = 0xff;   
    LCD_init();
    LCD_clear(0);
    pic_play(0,128,0,160);
//  pic_play(68,122,8,74);
// 	pic_play(7,61,82,148);
// 	pic_play(68,122,82,148);
    while(1);
}
