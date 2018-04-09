#include<reg51.h>
#include<AT24C04.c>
void delay(unsigned int x )
{
	while(x--);
}
void main()
{
	init_24c04();						 //I2总线初始化函数
	while(1)
	{
		write_add_dat_24c04(1,0x0f);	 //写入地址1，保存数据0x0f
		delay(300);						 //延时
		write_add_dat_24c04(2,0xf0);	 //写入地址二，保存数据0xf0
		delay(300);						 //延时
		P0 = read_add_dat_24c04(1);		 //读地址1，保存数据0x0f，并显示
		delay(50000);					 //延时
		P0 = read_add_dat_24c04(2);		 //读地址二，保存数据0xf0，并显示
		delay(50000);					 //延时
	}
}