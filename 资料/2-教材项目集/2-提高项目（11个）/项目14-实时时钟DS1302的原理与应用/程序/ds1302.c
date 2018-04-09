#include <reg51.h>
#define uchar unsigned char								//把 unsigned char 宏定义为 uchar
#define uint unsigned int								//把 unsigned int 宏定义为 uint
sbit rst = P3^4;										//定义复位/片选线接P3.4
sbit scl = P3^7;										//定义串行时钟引脚接P3.7
sbit sda = P3^5;										//定义串行数据输入输出端接P3.5
/*对DS1302初始化*/
void ds1302_init(void)
{
	rst = 0;
	scl = 0;
	rst = 1;
}
/*对DS1302写1字节函数*/
void write_ds1302_onebyte(unsigned char dat)	   
{
	unsigned char i;
	for(i = 0;i < 8;i++)
	{
		sda = (bit)(dat & 0x01);
		scl = 0;
		scl = 1;
		dat = dat >> 1;
	}
}
/*从DS1302读一字节函数*/
uchar read_ds1302_onebyte(void)		
{
	unsigned char i,dat;
	for(i = 0;i < 8;i++)
	{
		scl = 1;
		scl = 0;
		dat = dat >> 1;
		if(sda)dat = dat | 0x80;
	}
	return(dat);	
}
/*对DS1302的某一地址写一字节函数*/
void write_ds1302_add_dat(unsigned char add,unsigned char dat)
{
	ds1302_init();
	write_ds1302_onebyte(add);
	write_ds1302_onebyte(dat);
	scl = 1;
	rst = 0;
}
/*从DS1302的某一地址读一字节函数*/
uchar read_ds1302_add(unsigned char add)									
{
   unsigned char dat_temp;
	ds1302_init();
	write_ds1302_onebyte(add);
	dat_temp = read_ds1302_onebyte();
	scl = 1;
	rst = 0;
	return(dat_temp);
}
/*8421BCD码到十进制转换*/
uchar BCD_DEC_conv(unsigned char x)
{
	unsigned char dec;
	dec =  0x0f & x;
	x = x >> 4;
	dec	= dec + x * 10;
	return(dec);
}
uchar DEC_BCD_conv(unsigned char x)
{
	unsigned char bcd;
	bcd =  x % 10;
	x = x / 10;
	x = x << 4;
	bcd	= bcd | x ;
	return(bcd);
}
