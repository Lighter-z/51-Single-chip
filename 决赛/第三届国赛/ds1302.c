sbit SCK=P1^7;		
sbit SD=P2^3;		
sbit RST=P1^3;
/********************************************************************/ 
/*复位脚*/
#define RST_CLR	RST=0	/*电平置低*/
#define RST_SET	RST=1	/*电平置高*/
/*双向数据*/
#define SDA_CLR	SD=0	/*电平置低*/
#define SDA_SET	SD=1	/*电平置高*/
#define SDA_R	SD	/*电平读取*/	
/*时钟信号*/
#define SCK_CLR	SCK=0	/*时钟信号*/
#define SCK_SET	SCK=1	/*电平置高*/
/********************************************************************/ 
#define ds1302_sec_addr			0x80		//秒数据地址
#define ds1302_min_addr			0x82		//分数据地址
#define ds1302_hr_addr			0x84		//时数据地址
#define ds1302_date_addr		0x86		//日数据地址
#define ds1302_month_addr		0x88		//月数据地址
#define ds1302_day_addr			0x8A		//星期数据地址
#define ds1302_year_addr		0x8C		//年数据地址

#define ds1302_control_addr		0x8Ee		//写保护命令字单元地址
#define ds1302_charger_addr		0x90 		//涓电流充电命令字地址			 
#define ds1302_clkburst_addr	0xBE		//日历、时钟突发模式命令字地址


/********************************************************************/ 
/*单字节写入一字节数据*/
void Write_Ds1302_Byte(unsigned char dat) 
{
	unsigned char i;
	SCK = 0;
	for (i=0;i<8;i++) 
	{ 
	    SD=0;
		if (dat & 0x01) 	// 等价于if((addr & 0x01) ==1) 
		{
			SDA_SET;		//#define SDA_SET SDA=1 /*电平置高*/
		}
		else 
		{
			SDA_CLR;		//#define SDA_CLR SDA=0 /*电平置低*/
		}		 
		SCK_SET;
		SCK_CLR;		
		dat = dat >> 1; 
	} 
}
/********************************************************************/ 
/*单字节读出一字节数据*/
unsigned char Read_Ds1302_Byte(void) 
{
	unsigned char i, dat=0;	
	for (i=0;i<8;i++)
	{	
		dat = dat >> 1;
		if (SDA_R) 	  //等价于if(SDA_R==1)    #define SDA_R SDA /*电平读取*/	
		{
			dat |= 0x80;
		}
		else 
		{
			dat &= 0x7F;
		}
		SCK_SET;
		SCK_CLR;
	}
	return dat;
}

/********************************************************************/ 
/*向DS1302 单字节写入一字节数据*/
void Ds1302_Single_Byte_Write(unsigned char addr, unsigned char dat)
{ 

	RST_CLR;			/*RST脚置低，实现DS1302的初始化*/
	SCK_CLR;			/*SCK脚置低，实现DS1302的初始化*/

	RST_SET;			/*启动DS1302总线,RST=1电平置高 */
	addr = addr & 0xFE;	 
	Write_Ds1302_Byte(addr); /*写入目标地址：addr,保证是写操作,写之前将最低位置零*/	
	Write_Ds1302_Byte((dat / 10) << 4 | (dat % 10));	 /*写入数据：dat*/
	RST_CLR;				 /*停止DS1302总线*/
}

/********************************************************************/ 
/*从DS1302单字节读出一字节数据*/
unsigned char Ds1302_Single_Byte_Read(unsigned char addr) 
{ 
	unsigned char temp;
	unsigned char dat1,dat2;
	RST_CLR;			/*RST脚置低，实现DS1302的初始化*/
	SCK_CLR;			/*SCK脚置低，实现DS1302的初始化*/

	RST_SET;	/*启动DS1302总线,RST=1电平置高 */	
	addr = addr | 0x01;	 
	Write_Ds1302_Byte(addr); /*写入目标地址：addr,保证是读操作,写之前将最低位置高*/
	temp=Read_Ds1302_Byte(); /*从DS1302中读出一个字节的数据*/		
	RST_CLR;	/*停止DS1302总线*/
	dat1 = temp / 16;
	dat2 = temp % 16;
	temp = dat1 * 10 + dat2;
	return temp;
}

void DS1302_init()
{
	unsigned char i = 0,add = 0x80;
	Ds1302_Single_Byte_Write(0x8e,0x00);
	for(i = 0;i < 7;i++)
	{
		Ds1302_Single_Byte_Write(add,shijian[i]);
		add += 2;
	}
	Ds1302_Single_Byte_Write(0x8e,0x80);
}

void DS1302_Read()
{
	unsigned char i = 0,add = 0x81;
	Ds1302_Single_Byte_Write(0x8e,0x00);
	for(i = 0;i < 7;i++)
	{
		shijian[i] = Ds1302_Single_Byte_Read(add);
		add += 2;
	}
	Ds1302_Single_Byte_Write(0x8e,0x80);
}
