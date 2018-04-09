//AT24C04应用，教材和B105型实验开发板通用
//读取并且存储地址，
//设计：单片机创新工作室--齐霄涵设计，2015年12月15日
#include<reg51.h>								//头文件
#include<at24c04.c>								//包含AT24C04驱动的头文件
#define uint unsigned int
void delay(uint x)
{
	while(x--);
}
void main(void)
{
	init_2404();							   //AT24C04驱动
	while(1)
	{
		write_add_dat_2404(1,0x0f);			   //地址1保存0x0f
		delay(300);
		write_add_dat_2404(2,0xf0);			   //地址2保存0xf0
		delay(300);
		P0 = read_add_dat_2404(1);			   //读地址1保存0x0f，并在P0口显示
		delay(50000);
		P0 = read_add_dat_2404(2);			   //读地址2保存0xf0，并在P0口显示
		delay(50000);
	}
}