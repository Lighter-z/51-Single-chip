#include<stc15f2k60s2.h>
#include<intrins.h>
#include<iic.c>
#include<define.c>
#include<key.c>

void display()
{
	dianya = dianya * 0.039;
	if((dianya >= 0) && (dianya < 1))
	{
		zaizhong = 1;//¿Õ
		huo = 0;
		P2 = 0x80;
		P0 = 0xfe;
		
		P2 = 0xa0;
		P0 = 0x00;
	}
	else if((dianya >= 1) && (dianya <= 4))
	{
		zaizhong = 2;//·Ç¿Õ
		huo = 1;
		P2 = 0x80;
		P0 = 0xfd;
		
		P2 = 0xa0;
		P0 = 0x00;
	}
	else if(dianya > 4)
	{
		zaizhong = 3;//¹ýÔØ
		huo = 0;
		P2 = 0x80;
		P0 = 0xfb;
		if(fengming == 1)
		{
			P2 = 0xa0;
			P0 = 0x40;
		}
		else 
		{
			P2 = 0xa0;
			P0 = 0x00;
		}
	}
	
	
	
	if((zaizhong == 1) && (shezhi == 0))
	{
		yi = er = san = si = wu = liu = qi = ba = 11;
	}
	else if((zaizhong == 3)  && (huo == 0) && (shezhi == 0))
	{
		yi = 1;
		er = liu = qi = 11;
		san = juli / 100;;
		si = juli % 100 / 10;
		wu = juli % 10;
		ba = lei;
	}
	else if((huo == 1) && ((zaizhong == 2) && (shezhi == 0)))
	{
	//	huo = 0;
		if(yun == 1)
		{
				P2 = 0xa0;
				P0 = 0x10;
		}
		else 
		{
		
				P2 = 0xa0;
				P0 = 0x00;
		}
		if(tingzhi == 0)
		{
			P2 = 0x80;
			P0 = 0xfd;
		}
		else 
		{
			if(fengming == 1)
			{
				P2 = 0x80;
				P0 = 0xf5;
			}
			else 
			{
				P2 = 0x80;
				P0 = 0xfd;
			}
		}
		yi = 2;
		er = san = si = wu = liu = 11;
		qi = shijian / 10;
		ba = shijian % 10;
	}
	
	if(shezhi == 1)
	{
		yi = 3;
		er = san = liu = 11;
		if(fengming == 1)
		{
			si = shijian_yi_t / 10;
			wu = shijian_yi_t % 10;
		}
		else
		{
			si = wu = 11;
		}
		qi = shijian_er_t / 10;
		ba = shijian_er_t % 10;
	}
	else if(shezhi == 2)
	{
		yi = 3;
		er = san = liu = 11;
		if(fengming == 1)
		{
			qi = shijian_er_t / 10;
			ba = shijian_er_t % 10;
		}
		else
		{
			qi = ba = 11;
		}
		si = shijian_yi_t / 10;
			wu = shijian_yi_t % 10;
	}
}

void main()
{
	banzi_init();
	Timer0Init();
	Timer1Init();
	EA = 1;
	ET0 = 1;
//	IIC_Write(0x01,2);
//					Delay1ms();
//					IIC_Write(0x02,4);
	while(1)
	{
		dianya = AD(0x03);
		
		ceju();
		keyscan();
		display();
//		
//		yi = dianya / 10;
//		er = dianya % 10;
//		san = si = wu = liu = qi = ba = 11;
		
//		yi = juli / 100;
//		er = juli % 100 / 10;
//		san = juli % 10;
//		si = wu = liu = qi = ba = 11;
		xianshi();
	}
}
