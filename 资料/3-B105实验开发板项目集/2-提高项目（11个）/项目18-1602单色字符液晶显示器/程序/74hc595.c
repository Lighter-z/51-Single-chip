#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit SH_CP1 = P0^2;//定义
sbit DS1 = P0^0;//串行数据的输入端
sbit ST_CP1 = P0^1;//控制锁存器的输出
void send1(uchar x)
{
	uchar i;
	for(i = 0;i < 8;i++)
	{
		SH_CP1 = 0;
		DS1 = (bit)(x & 0x01);
		x = x >> 1;
		SH_CP1 = 1;
	} 
	ST_CP1 = 0;
	ST_CP1 = 1;
}	