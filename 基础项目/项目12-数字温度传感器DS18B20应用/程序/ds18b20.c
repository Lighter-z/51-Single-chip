/*delay（10）约等于50微妙 */
#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int 
sbit DQ=P1^2;
void delay(unsigned char x)
{
	while(x--);
}
/*初始化函数*/
void init_ds18b02()
{
	uchar x = 255;
	DQ = 1;				  //先让DQ置1
	DQ = 0;				  //DQ拉低
	delay(80);			  //延时480-960us
	DQ = 1;				  //释放总线
	while(DQ&&x--);		  //等待返回的低电平，若没有响应，适当延时自动向下执行
	delay(20);			  //延时
}
/*向18B20中写一个字节 */
void Write_OneChar(uchar dat)
{
	uchar i = 0;
	for(i=8;i>0;i--)	  //循环8次得出数据
	{	
		DQ = 0;			  //DQ先置低电平
		DQ = dat&0x01;	  //取最低位
		delay(10);		  //延时大约15us
		DQ = 1;			  //释放总线
		dat = dat>>1;	  //由低位向高位发送数据
	}
	delay(8);
}
/*向18B20中读一个字节 */
uchar Read_OneChar(void)
{
	uchar i = 0;
	uchar dat = 0;
	for(i=8;i>0;i--)	  //循环8次得出数据
	{
		DQ = 0;			  //发送启动信号
		dat = dat>>1;
		DQ = 1;			  //释放总线
		if(DQ)			  //判断总线是否为高电平
		dat = dat|0x80;	  //若是，dat最高位置1，不是置0
		delay(10);		  //延时
	}
	return(dat);
}
/*读温度 */
uchar a,b,c;
uchar Read_Temperature()
{
	uchar i = 0,t = 0;
	init_ds18b02();			    //启动DS18B20
	Write_OneChar(0xcc);		//跳过读序列号的操作
	Write_OneChar(0x44);		//启动温度转化
	init_ds18b02();				//启动DS18B20
	Write_OneChar(0xcc);		//跳过读序列号的操作
	Write_OneChar(0xbe);		//读取温度寄存器等（共可读9个寄存器）前两个是温度
	a = Read_OneChar();			//读取温度低位
	b = Read_OneChar();			//读取温度高位
	c = 0x0f&a;					//得到小数部分
	a = a>>4;					//低位右移4位
	b = b<<4;					//高位左移4位
	t = a|b;					//得到8位温度的整数部分，最高位1为符号位
	return (t);

}
/*保持温度上下线*/
void  write_temprom(uchar temp_up_set,uchar temp_down_set)
{
	init_ds18b02();			    //启动DS18B20
	Write_OneChar(0xcc);		//跳过读序列号的操作
	Write_OneChar(0x4e);		//准备写暂存器
	Write_OneChar(temp_up_set);	//写入温度上限	
	Write_OneChar(temp_down_set);	//写入温度下限
	Write_OneChar(0x7f);
	init_ds18b02();			    //启动DS18B20
	Write_OneChar(0xcc);		//跳过读序列号的操作
	Write_OneChar(0x48);		//复制暂存器到ROM中
	init_ds18b02();			    //启动DS18B20
	Write_OneChar(0xcc);		//跳过读序列号的操作
	Write_OneChar(0xb8);		//重调E2PROM	
}				   
/*读取温度上下线*/
uchar temp_up,temp_down;
void read_temprom()
{
	uchar i;
    init_ds18b02();			    //启动DS18B20
	Write_OneChar(0xcc);		//跳过读序列号的操作
	Write_OneChar(0xbe);		//读取温度寄存器等（共可读9个寄存器） 前两个就是温度
	i = Read_OneChar();			//读0地址寄存器，扔掉
	i = Read_OneChar();			//读1地址寄存器，扔掉
	temp_up = Read_OneChar();	//读2地址寄存器
	temp_down = Read_OneChar();	//读3地址寄存器
}		 