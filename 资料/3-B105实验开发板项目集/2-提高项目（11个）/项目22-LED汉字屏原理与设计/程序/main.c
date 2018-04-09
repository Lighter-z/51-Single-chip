//LED汉字显示，针对B105型实验开发板设计
//通过LED屏显示数字
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char 
#define uint unsigned int
sbit  ds1 = P2^1;
sbit  sh_cp1 = P2^0;
sbit  st_cp1 = P2^2;
sbit  ds2 = P2^6;
sbit  sh_cp2 = P2^5;
sbit  st_cp2 = P2^7;
sbit  OE = P2^3;
sbit  e = P2^4;
extern uchar code dat[];
extern void dat595(uchar as,uchar bs);									//声明HC595传入数据函数
extern void shuchu();													//声明HC595输出数据函数
extern void suocun();													//声明HC595锁存数据函数
/************汉字取模**************************/
uchar code dat[] = {
/*--  文字:  手  --*/
/*--  Times New Roman12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x24,0x24,0x24,0x24,0x24,0x24,0x7F,0x44,0x44,0x44,0x44,0x44,0x04,0x00,0x00,
0x40,0x40,0x40,0x40,0x40,0x42,0x41,0xFE,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
/*--  文字:  机  --*/
/*--  Times New Roman12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x10,0x13,0xFF,0x12,0x11,0x10,0x00,0x7F,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,
0x20,0xC0,0x00,0xFF,0x00,0x82,0x0C,0x30,0xC0,0x00,0x00,0x00,0xFC,0x02,0x1E,0x00,
};
void dat595(uchar as,uchar bs)											//向HC595传入数据
{
	uchar i,b;
	e = 1;																			
	b = bs;																//先写第二个参数，即取模的时候汉字字模的第二排数据（共16个），写到16*16点阵的下面2个8*8点阵 
	for(i = 0; i < 8; i++)
	{					  		
		ds1 = b & 0x01;													//写参数2的最低位	
		sh_cp1 = 0;	 
		_nop_();_nop_();_nop_();										//空操作，
		sh_cp1 = 1;														//在时钟上升沿写入数据
		b >>= 1;														//右移一位
	}	
	b = as; 
	for(i = 0; i < 8; i++)												//再写第一个参数，即取模的时候汉字字模的第一排数据（共16个），写到16*16点阵的上面2个8*8点阵
	{	
		ds1 = b&0x01;													//写参数1的最低位
		sh_cp1 = 0;	 
		_nop_();_nop_();_nop_();
		sh_cp1 = 1;														//在时钟上升沿写入数据
		b >>= 1;														//右移一位
	}
}
void shuchu()															//HC595输出数据
{
	st_cp2 = 0;	
	st_cp1 = 0;
	st_cp2 = 1; 														//在时钟上升沿输出数据
	st_cp1 = 1;															//在时钟上升沿输出数据
}																		
void suocun()															//HC595锁存数据
{
	sh_cp2 = 0;															//在时钟上升沿写入数据
	sh_cp2 = 1;	
	ds2 = 1;
}
void main(void)
{
	uchar j;
	while(1)
	{
		OE = 0 ;
		ds2= 0 ;														//一次选中
		for(j  =0; j < 16; j++)											//写入"手"字的点阵，
		{
			dat595(dat[j],dat[16+j]);
			suocun();													//HC595锁存函数
			shuchu();													//HC595输出函数
		} 	 
		for(j = 0; j < 16; j++)											//写入"真"字的点阵，
		{
			dat595(dat[32 + j], dat[32 + 16 +j ]);
			suocun();
			shuchu();
		}
	}
}

