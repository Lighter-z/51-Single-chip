//15单片机内部EEPROM使用，针对B105型实验开发板设计
//可以在应用可编程（IAP），本项目利用IAP技术保存时分秒数据,然后再读出并显示
//设计：单片机创新工作室----冷恩鑫设计，2015年12月15日
#include<reg51.h>
#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
#include<display.c>
#include<15fe2prom.c>
uint cp1,cp3;
void timer0_isr(void) interrupt 1
{
	TH0 =  (65536 - 1000) / 256;
	TL0 =  (65536 - 1000) % 256;
	cp1++;
	if(cp1 >= 500)							//半秒
	{
		cp1 = 0;
		cp3++;
		flash = ~flash;
	}
	P0 = 0xff;
	display();								//去显示
	cp2++;
	if(cp2 >= 8)cp2 = 0;			
}
void timer0_init(void)
{
	TMOD = 0x01;
	TH0 =  (65536 - 1000) / 256;
	TL0 =  (65536 - 1000) % 256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}
void main(void)
{
	timer0_init();
	hour = IAP_ReadByte(0xa800);			//再读保存的时间
	min = read_dat_1b(0xaa00);
	sec = read_dat_1b(0xac00);
	while(1)
	{
		if(cp3 >= 2)						//1秒到了
		{	
			cp3 = 0;
			sec++;

			if(sec >= 60){sec = 0;min++;}
			if(min >= 60){min = 0;hour++;}
			if(hour >= 24)hour = 0;
			save_dat_1b(0xa800,20);			//保存时间
//			save_dat_1b(0xaa00,30);
//			save_dat_1b(0xac00,10);
			IAP_EraseSector(0xa800);
			IAP_WriteByte(0xa800,hour);
			IAP_EraseSector(0xaa00);
			IAP_WriteByte(0xaa00,min);
			IAP_EraseSector(0xac00);
			IAP_WriteByte(0xac00,sec);
		}	
	}
}