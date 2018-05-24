#include<stc15f2k60s2.h>
#include<define.c>
#include<iic.c>
#include<ds1302.c>
#include<key.c>
sbit sbuzz = P3^4;
void display()
{
	if(moshi == 0)
	{
		if(tiaoshi == 0)
		{
			yi = shijian[2] / 10;
			er = shijian[2] % 10;
			san = 10;
			si = shijian[1] / 10;
			wu = shijian[1] % 10;
			liu = 10;
			qi = shijian[0] / 10;
			ba = shijian[0] % 10;
		}
		else if(tiaoshi == 1)
		{
			if(shijian[0] % 2 == 0)
			{
				yi = shijian[2] / 10;
				er = shijian[2] % 10;
			}
			else 
			{
				yi = 10;
				er = 10;
			}
			san = 10;
			si = shijian[1] / 10;
			wu = shijian[1] % 10;
			liu = 10;
			qi = shijian[0] / 10;
			ba = shijian[0] % 10;
		}
		else if(tiaoshi == 2)
		{
			if(shijian[0] % 2 == 0)
			{
				si = shijian[1] / 10;
				wu = shijian[1] % 10;
			}
			else 
			{
				si = 10;
				wu = 10;
			}
			yi = shijian[2] / 10;
			er = shijian[2] % 10;
			san = 10;			
			liu = 10;
			qi = shijian[0] / 10;
			ba = shijian[0] % 10;
		}
		else if(tiaoshi == 3)
		{
			if(shijian[0] % 2 == 0)
			{
				qi = shijian[0] / 10;
				ba = shijian[0] % 10;		
			}
			else 
			{
				ba = 10;
				qi = 10;
			}
			yi = shijian[2] / 10;
			er = shijian[2] % 10;
			san = 10;		
			si = shijian[1] / 10;
			wu = shijian[1] % 10;			
			liu = 10;
		}
	}
	else if(moshi == 1)
	{
		yi = juli / 100;
		er = juli % 100 / 10;
		san = juli % 10;
		si = 11;
		wu = 11;
		liu = baojingjuli / 100;
		qi = baojingjuli % 100 / 10;
		ba = baojingjuli % 10;
		if(juli <= baojingjuli)
		{
			if(juli < (float)(1.2 * baojingjuli))
			{
				P2 = 0x80;
				P0 = 0xfe;
			}
			else 
			{
				P2 = 0xa0;
				P0 = 0x40;
			}
		}
		else if(juli >= baojingjuli)
		{
			P2 = 0xa0;
			P0 = 0x00;
			P2 = 0x80;
			P0 = 0xff;
		}
	}
}

void main()
{
	quanliang();
	Delay1000ms();
	banzi_init();
	Timer0Init();
	Timer1Init();
	EA = 1;
	ET0 = 1;
	Write_DS1302();
	sbuzz = 1;
	while(1)
	{
		ceju();
		Read_DS1302();
		keyscan();
		display();
		
		xianshi();
	}
}