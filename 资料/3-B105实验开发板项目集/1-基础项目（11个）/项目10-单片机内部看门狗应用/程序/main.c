//单片机内部看门狗应用，教材和B105型实验开发板通用
//启动看门狗，设定看门狗溢出时间为一秒，若看门狗溢出后复位，LED灯不停闪烁	
//河南科技学院-单片机协会，2016年10月9日		 
#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
sfr WDT_CONTR = 0xe1;			//定义单片机内部看门狗寄存器
sbit LED = P0^0;
void delay(uint x)
{
	while(x--);
}
void main(void)
{
	WDT_CONTR = 0x24;			//启动看门狗，设定看门狗溢出时间为一秒	
	while(1)
	{
		//WDT_CONTR = 0x14;		//喂狗，若屏蔽此句，则看门狗溢出后复位，LED灯不停闪烁
		LED = 1;
		delay(50000);
		LED = 0;
		delay(50000);	;
	}
}