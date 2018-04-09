#include <reg51.h>
#define uchar unsigned char								//把 unsigned char 宏定义为 uchar
#define uint unsigned int								//把 unsigned int 宏定义为 uint
uchar month,year,date,sec,min,hour,week;
sbit rst = P3^4;										//定义复位/片选线接P3.4
sbit sclk = P3^7;										//定义串行时钟引脚接P3.7
sbit sda = P3^5;										//定义串行数据输入输出端接P3.5
/*对DS1302初始化*/
void ds1302_init(void)
{
	rst = 0;										   //rst为低电平
	sclk = 0;										   //sclk为低电平时，才能将rst置为高电平
	rst = 1;										   //rst为高电平
}
/*对DS1302写1字节函数*/
void write_ds1302_onebyte(unsigned char dat)	   
{
	unsigned char i;
	for(i = 0;i < 8;i++)							   //循环8次，得出一字节数据
	{
		sda = (bit)(dat & 0x01);					  //强制取最低位
		sclk = 0;									  //低电平          上升沿写入数据
		sclk = 1;									 //高电平
		dat = dat >> 1;								 //数据由低到高输入
	}
}
/*从DS1302读一字节函数*/
uchar read_ds1302_onebyte(void)		
{
	unsigned char i,dat;
	for(i = 0;i < 8;i++)							 //循环8次，得出一字节数据
	{
		sclk = 1;									//低电平            下降沿读出数据
		sclk = 0;									//高电平
		dat = dat >> 1;								//由低到高读出
		if(sda)dat = dat | 0x80;					//如果读出的数据是1，将1取出，放在最高位
	}
	return(dat);								   //将数据返回
}
/*对DS1302的某一地址写一字节函数*/
void write_ds1302_add_dat(unsigned char add,unsigned char dat)
{
	ds1302_init();			 //启动
	write_ds1302_onebyte(add);	//写入命令
	write_ds1302_onebyte(dat);	//写入数据
	sclk = 1;					//将时钟电平置于已知状态
	rst = 0;					//禁止数据传递
}
/*从DS1302的某一地址读一字节函数*/
uchar read_ds1302_add(unsigned char add)	//读1302的数据								
{
   unsigned char dat_temp;
	ds1302_init();				  //启动
	write_ds1302_onebyte(add);			//写命令
	dat_temp = read_ds1302_onebyte();  //读数据
	sclk = 1;						  //将时钟电平置于已知状态
	rst = 0;						 //禁止数据传递
	return(dat_temp);			   //将数据返回
}
/*8421BCD码到十进制转换*/
uchar BCD_DEC_conv(unsigned char x)
{
	unsigned char dec;
	dec =  0x0f & x;				//保留低四位
	x = x >> 4;			   		   //高四位变为低四位
	dec	= dec + x * 10;			  //转换为十进制
	return(dec);
}
/*十进制转换到8421BCD码*/
uchar DEC_BCD_conv(unsigned char x)
{
	unsigned char bcd;
	bcd =  x % 10;		  		  //取余，低四位
	x = x / 10;					  //取整，高四位
	x = x << 4;					  //低四位变为高四位
	bcd	= bcd | x ;				  //或运算，得出BCD码
	return(bcd);
}
/*获得时间信息函数*/
void get_ds1302_time(void)													//获取1302的时间数据（时、分、秒），存入time1数组中
{
	unsigned char d;
	d = read_ds1302_add(0x81);												//读秒
	sec = BCD_DEC_conv(d);													//得到秒	
	d = read_ds1302_add(0x83);												//读分
	min = BCD_DEC_conv(d);													//得到分
	d = read_ds1302_add(0x85);												//读小时
	hour = BCD_DEC_conv(d);													//得到小时
	d = read_ds1302_add(0x87);												//读日
	date = BCD_DEC_conv(d);													//得到日
   	d = read_ds1302_add(0x89);												//读月
	month = BCD_DEC_conv(d);												//得到月
	d = read_ds1302_add(0x8b);												//读星期
	week = BCD_DEC_conv(d);													//得到星期
	d = read_ds1302_add(0x8d);												//读年
	year = BCD_DEC_conv(d);													//得到年		
}
