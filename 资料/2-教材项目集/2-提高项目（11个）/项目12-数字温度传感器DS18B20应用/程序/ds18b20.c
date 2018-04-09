#define uchar unsigned char
#define uint unsigned int
sbit DQ = P1^2;													//定义单片机的P2.7与DS18B20数据端口连接在一起                                    													 
/********延时函数********/
void delay(uint x)
{
	while(x--); 
}
/********初始化函数********/
void Init_DS18B20(void)											//基本操作函数1
{
	unsigned char x = 255;
	DQ = 1;														//先让DQ置1
	DQ = 0;														//单片机将DQ拉低
	delay(80);													//延时480-960us
	DQ = 1;														//释放总线
	while(DQ && x--);											//等待返回的低电平响应 如果没有响应，则做适量延时自动往下执行
	delay(20);
}
/********从DS18B20中读一个字节********/
uchar Read_OneChar(void)										//基本操作函数2
{
	uchar i = 0;
	uchar dat = 0;
	for (i=8;i>0;i--)
	{
  		DQ = 0;													//发送启动信号
  		dat >>= 1;									  	
  		DQ = 1;													//释放总线
  		if(DQ)													//判断总线是否为高电平
  		dat |= 0x80;											//如果是高电平，则把dat的最高位置1，如果不是，默认置0
  		delay(10);
	}
	return(dat);
}
/********向18B20中写一个字节********/
void Write_OneChar(uchar dat)									//基本操作函数3
{
	uchar i=0;
	for (i=8; i>0; i--)
	{
		DQ = 0;
		DQ = dat & 0x01;										//取dat的最低位
		delay(10);
		DQ = 1;
		dat >>= 1;
	}
	delay(8);
}
/********读取温度********/
uchar a,b,c;
uchar Read_Temperature(void)									//应用操作函数1
{
	uchar i = 0,t = 0;
	Init_DS18B20();
	Write_OneChar(0xcc);										// 跳过读序号列号的操作
	Write_OneChar(0x44);										// 启动温度转换
	Init_DS18B20();
	Write_OneChar(0xcc);										//跳过读序号列号的操作
	Write_OneChar(0xbe);										//读取温度寄存器等（共可读9个寄存器） 前两个就是温度
	a = Read_OneChar();											//读取温度值低位
	b = Read_OneChar();											//读取温度值高位
	c = 0x0f & a;												//得到小数部分
	a = a >> 4;													//低位右移4位
	b = b << 4;													//高位左移4位
     t = a | b;													//得到8位温度的整数部分，最高1位为符号位
	return(t);
}
/********保存温度上下限********/
void write_temprom(uchar temp_up_set,uchar temp_down_set )		//应用操作函数2
{
 	Init_DS18B20();
	Write_OneChar(0xcc);										//跳过读序号列号的操作
	Write_OneChar(0x4e);										//写准备 
	Write_OneChar(temp_up_set);									//向18B20的暂存写上限		 
	Write_OneChar(temp_down_set);								//向18B20的暂存写下限
	Write_OneChar(0x7f);
	Init_DS18B20();
	Write_OneChar(0xcc); 
	Write_OneChar(0x48);										//向18B20的rom中写数据
	Init_DS18B20();
	Write_OneChar(0xcc);
	Write_OneChar(0xb8);
} 
/********读取温度上下限********/
uchar  temp_up,temp_down;										//温度上下限值
void read_temprom(void)											//应用操作函数3
{
   	uchar i;
	Init_DS18B20();
	Write_OneChar(0xcc);										//跳过读序号列号的操作        	
	Write_OneChar(0xbe);										//读取温度寄存器等（共可读9个寄存器） 前两个就是温度
	i = Read_OneChar();											//读0地址寄存器，扔掉
	i = Read_OneChar();											//读1地址寄存器，扔掉
	temp_up = Read_OneChar();									//读2地址寄存器
	temp_down = Read_OneChar();									//读3地址寄存器
}

