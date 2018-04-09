//TLC549应用，针对教材设计
//实时读取读取tlc549的检测电压数据
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg52.h>
#include<tlc549.c>
code uchar  seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,									  	
							0x92,0x82,0xf8,0x80,0x90};											//数字0~9的显示方法
uchar cp1,cp2;
uint dat_ad;
/***************中断T0初始化函数**************/
void timer0_isr(void) interrupt 1																// timer0中断服务函数
{
	TL0 = (65535 - 5000) % 255;
	TH0 = (65535 - 5000) / 255;             
	cp1++;
	if(cp1 >= 100) 																				//0.5秒
	{
		cp1 = 0;
		dat_ad = tlc549_ad();
		dat_ad = dat_ad * 1.96;																		//数据255对应模拟电压5V 
	}
	P0 = 0xff;																					//Protuse仿真时用于消隐
	switch(cp2)
	{
		case 0: P0 = seven_seg[dat_ad % 10];P2 = ~0x01; break;   	
		case 1: P0 = seven_seg[dat_ad / 10 %10];P2 = ~0x02; break;   	
		case 2: P0 = seven_seg[dat_ad / 100] & 0x7f;P2 = ~0x04; break;							//加上小数点 	
	}                
	cp2++;
	if(cp2 >= 3)
	cp2 = 0;
}
/**************中断T0中断服务函数************/
void timer0_init (void)            																// timer0中断初始化函数
{                   
	TMOD = 0x01;                                  
	TL0 = (65535 - 5000) % 255;
	TH0 = (65536 - 5000) / 256;                                     
	ET0 = 1;                     
	EA = 1;                      
	TR0 = 1;                      
}
/**************主函数*********************/ 						
void main(void)				 																	//主程序
{  
	timer0_init();
	while(1);
}