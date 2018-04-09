#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar num[] = "0123456789";							//显示两位数字时使用
sbit RS = P1^7;										//数据命令选择端
sbit RW = P1^6;										//读写选择端
sbit E  = P1^5;										//使能信号端
/*延时函数*/
void delay(uint x)
{
	while(x--);
}
/*向1602写一个命令*/
void write_command(uchar command)
{
	RW = 0;			 //
	RS = 0; 		 //
	P0 = command;	 //
	E = 1;			 //
	delay(100);		//								//等待接收，省略了读状态操作
	E = 0;			//
	RW = 1;			//
}
/*向1602写一个数据*/
void write_data(uchar date)
{
	RW = 0;
	RS = 1; 	
	P0 = date; 
	E = 1;
	delay(100);										//等待接收
	E = 0;
	RW = 1;
}
/*初始化1602*/
void F1602_init(void)
{
	write_command(0x38);							// 两行，每行16字符，每个字符5*7点阵	
	write_command(0x0f);							// 光标显示并闪烁
	//write_command(0x0C);							// 光标不显示
	write_command(0x06);							// 光标随字符右移
}
/*对1602清屏*/
void F1602_clear()
{
	write_command(0x01);	
	write_command(0x02);	
}
/*向1602写字符串*/
void display_string(uchar *p)
{												
	while(*p)										//字符非空
	{
		write_data(*p);								//写字符
		p++;										//数据指针加1
	}
}
/*向1602写数字变量(两位)**/
void display_num(uchar x)
{
	 write_data(num[x / 10]);
	 write_data(num[x % 10]);	
}
/*定位*/
void gotoxy(uchar y,uchar x)
{
	if(y == 1)
	write_command(0x80 + x);						//第一行
	else if(y == 2)
	write_command(0x80 + 0x40 + x);	//第二行
}
	
