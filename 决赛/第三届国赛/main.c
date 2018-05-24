#include<stc15f2k60s2.h>
#include<define.c>
#include<ds1302.c>
#include<iic.c>
#include<chaoshengbo.c>
#include<key.c>
#include<display.c>

void main()
{
	banzi_init();
//	for(z = 0;z < 6;z++)
//	{
//		Write_AT24c04(add,anwser[z]);
//		Delay1ms();
//		add = add + 1;
//	}
	add = 0x01;
	for(z = 0;z < 6;z++)
	{
		anwser[z] = Read_AT24c04(add);
		Delay1ms();
		add = add + 1;
	}
	DS1302_init();
	Timer0Init();
	Timer1Init();
	EA = 1;
	ET0 = 1;
	while(1)
	{
		keyscan();
		DS1302_Read();
		display();
	}
}
