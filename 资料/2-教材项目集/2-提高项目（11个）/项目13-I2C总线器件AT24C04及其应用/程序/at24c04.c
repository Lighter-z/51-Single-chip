/***************************************************************/
/******************AT24C04驱动——2015年12月15日*******************/
/***************************************************************/
#include <intrins.h>					  //库函数的头文件
#define uchar unsigned char				  //宏定义，用uchar代替unsigned char
#define nop _nop_()
sbit sda = P1^0;						  //将sda接P1.0端口
sbit scl = P1^1;						  //将scl接P1.1端口
/****************************I2C总线开始*************************/
void start_2404(void)
{
	sda = 1;
	nop;
	scl = 1;
	nop;
	sda = 0;
	nop;
	scl = 0;
	nop;
}
/****************************I2C总线停止*************************/ 
void stop_2404(void)
{
	sda = 0;
	nop;
	scl = 1;
	nop;
	sda = 1;
	nop;
}
/****************************应答程序*************************/
void ack_2404(void)
{
	uchar i = 255;
	scl = 1;
	nop;
	while(sda && i--);
	scl = 0;
	nop;
}
/****************************I2C总线初始化*************************/
void init_2404(void)
{
	sda = 1; nop;	   					//常态
	scl = 1; nop;	   					//常态
}
/****************************读出一字节*************************/
uchar read_onebyte_2404(void)
{
	uchar i, dat;
	sda = 1; 							//释放总线
	for(i = 8; i > 0; i--)
	{
		scl = 1;
		dat <<= 1;
		if(sda) dat |= 0x01;
		scl = 0;
	}
	sda = 1; scl = 0;
	return(dat);
}
/****************************写入一个字节*************************/
void write_onebyte_2404(uchar dat)
{
	uchar i;
	for(i = 8; i > 0; i--)
	{
		sda = (bit)(dat & 0x80);		//先发送数据的高位
		dat <<= 1;
		scl = 1;
		scl = 0;
	}
	sda = 1; scl = 0;
}
/****************************对某一地址写一个字节数据*************************/
void write_add_dat_2404(uchar add, uchar dat)
{
	start_2404();
	write_onebyte_2404(0xa0);
	ack_2404();
	write_onebyte_2404(add);
	ack_2404();
	write_onebyte_2404(dat);
	ack_2404();
	stop_2404();
}
/****************************读某一地址某一个字节数据*************************/
uchar read_add_dat_2404(uchar add)
{
	uchar dat;
	start_2404();
	write_onebyte_2404(0xa0);
	ack_2404();
	write_onebyte_2404(add);
	ack_2404();
	start_2404();
	write_onebyte_2404(0xa1);
	ack_2404();
	dat = read_onebyte_2404();
	stop_2404();
	return(dat);
}