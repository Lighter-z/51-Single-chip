#include<intrins.h>
#define uchar unsigned char 
#define nop _nop_()
sbit sda = P3^6;	   //sda接在P3^6
sbit scl = P3^7;	  //scl接在P3^7
/*I2总线启动*/
void start_24c04()	  //scl为高电平时，SDA由高向低跳变，开始传送数据
{
	scl = 1;nop;	  
	sda = 1;nop;
	sda = 0;nop;
	scl = 0;
}
/*I2总线停止*/
void stop_24c04()	  //scl为高电平时，SDA由低向高跳变，结束传送数据
{
	sda = 0;nop;	 
	scl = 1;nop;
	sda = 1;nop;
}
/*应答程序*/
void ack_24c04()
{
	uchar i = 255;
	scl = 1;nop;
	while(sda&&i--);	   //等待返回的低电平，若没有响应，适当延时自动向下执行
	scl = 0;nop;
}
/*I2总线初始化*/
void init_24c04()
{
	sda = 1;nop;     //常态
	scl = 0;nop;	 //常态
}
/*读取一个字节*/
uchar read_onebyte_24c04()
{
	uchar i,dat;
	sda = 1;						   //释放总线
	for(i = 0;i<8;i++)	              //循环八次，得到八位的数据
	{
		scl = 1;					   //scl为高电平时，检测sda状态
		dat = dat<<1;				  //由高位向低位读取
		if(sda)						  //判断sda是否为高电平
		dat = dat|0x01;		  		  //若是，dat最低位置一，不是则为0
		scl = 0;					  //scl置低电平
	}
	sda = 1;						 //应答
	scl = 0;						 //    信号
	return(dat);
}
/*写入一个字节*/
void write_onebyte_24c04(uchar dat)
{
	uchar i;
	for(i=0;i<8;i++)				  //循环八次，得到八位的数据
	{
		sda = (bit)(dat&0x80);		  //取最高位
		dat = dat<<1;				  //由高位向低位写入
		scl = 1;
		scl = 0;
	}
	sda = 1;						 //应答
	scl = 0;						 //    信号
}
/*对某个地址写一字节的数据*/
void write_add_dat_24c04(uchar add,dat)
{
	start_24c04();					 //启动
	write_onebyte_24c04(0xa0);		 //对AT24C04写操作
	ack_24c04();					 //应答
	write_onebyte_24c04(add);		 //写入数据存放地址
	ack_24c04();					 //应答
	write_onebyte_24c04(dat);		 //写入数据
	ack_24c04();					 //应答
	stop_24c04();					 //停止
}
/*读取某个地址一字节数据*/
uchar read_add_dat_24c04(uchar add)
{
	uchar dat;
	start_24c04();					 //启动
	write_onebyte_24c04(0xa0);		 //对AT24C04写操作
	ack_24c04();					 //应答
	write_onebyte_24c04(add);		 //写入将要读的数据地址
	ack_24c04();					 //应答
	start_24c04();					 //启动
	write_onebyte_24c04(0xa1);		 //对AT24C04读操作
	ack_24c04();					 //应答
	dat = read_onebyte_24c04();		 //赋值
	stop_24c04();					 //停止
	return (dat);
}