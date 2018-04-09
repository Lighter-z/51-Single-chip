#include<reg51.h>
#include<ds1302.c>

unsigned char flash;
unsigned char cp1,cp2,cp3;													//定义变量
sbit P1_0 = P1^0;															
code unsigned char seven_seg[13] = {0xc0,0xf9,0xa4,0xb0,0x99,
										0x92,0x82,0xf8,0x80,0x90,0xbf,0xff,0x7f};			//数字0~9的显示方法
code unsigned char scan[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};		//位选数组
bit conv;

void send(unsigned int x,unsigned int y)									//x表示位选，y表示段选
{
	P1_0 = 0;
	P1_0 = 1;
	P0 = scan[x];
	P1_0 = 0;																//P1.0端口高电平允许存储，P1.0为低电平保存存储
	P0 = seven_seg[y];			
}
void time0_isr(void) interrupt 1											//利用中断对数码管上显示的数据进行刷新
{
	TH0 = (65536 - 2000) / 256;											   //TH0重置函数
	TL0 = (65536 - 2000) % 256;											  //TL0重置函数
	cp1++;
	if(cp1 >= 250)															//0.5秒
	{
		cp1 = 0;
		flash = ~flash;														//产生闪烁变量
		cp2++;
		if(cp2 >= 5)
		{  
			cp2 = 0;
			conv = ~conv;												//产生交替显示变量	
		}	
	}
	if(conv == 1)
	{
		P0 = 0xff;
		switch(cp3)
		{
			case 0:	send(0,sec % 10);break;								//显示秒个位
			case 1: send(1,sec / 10);break;								//显示秒十位
			case 2:	if(flash)send(2,11);								//不显示
					else send(2,10);break;								//显示 -
			case 3: send(3,min % 10);break;								//显示分个位
			case 4:	send(4,min / 10);break;								//显示分十位
			case 5:	if(flash)send(5,11);								//不显示
					else send(5,10);break;								//显示 -
			case 6:	send(6,hour % 10);break;							//显示小时个位
			case 7:	send(7,hour / 10);break;							//显示小时十位		
		}
	}
	else
	{	
		P0 = 0xff;														//消隐
		switch(cp3)
		{
			case 0:	send(0,date % 10);break;								//显示天个位
		 	case 1:	send(1,date / 10);break;								//显示天十位
			case 2:	send(2,month % 10);break;								//显示月个位,
			case 3:	send(3,month / 10);break;								//显示月十位
			case 4:	send(4,year % 10);break;								//显示年个位
			case 5:	send(5,year / 10);break;								//显示年十位
			case 6:	send(6,0);break;										//显示0
			case 7:	send(7,2);break;										//显示2
		}
	}  
	cp3++;
	if(cp3 >= 8)cp3 = 0;			
}
void timer0_init(void)														//Timer0初始化
{																			//方式一
	TMOD = 0x01;															//TH0 预置，65536十六进制低8位。
	TH0 = (65536 - 2000) / 256;												//TL0 预置，65536十六进制低8位。
	TL0 = (65536 - 2000) % 256;
	TR0 = 1;															   //定时器T0开
	ET0 = 1;															   //溢出中断控制位T0开
	EA  = 1;															   //总开关打开
}
void main(void)
{
	unsigned char i = 46;											//举例，比如要调整时间，分钟设定为46分
	i = DEC_BCD_conv(i);
	timer0_init();
	write_ds1302_add_dat(0x8e,0x00);						    	//写操作，可以对DS1302调整
	write_ds1302_add_dat(0x80,0x30);								//写秒，30秒
	write_ds1302_add_dat(0x82,i);							    	//写分，46分
	write_ds1302_add_dat(0x84,0x12);								//写时，12时
	write_ds1302_add_dat(0x86,0x28);								//写日，28日
	write_ds1302_add_dat(0x88,0x05);								//写月，5月 
	write_ds1302_add_dat(0x8a,0x03);								//写星期，星期三
	write_ds1302_add_dat(0x8c,0x12);								//写年，（20）12年
	write_ds1302_add_dat(0x8e,0x80);								//写保护
	while(1)
	{
		get_ds1302_time();
	}
}
