#include<stc15f2k60s2.h>
#include<define.c>
#include<ds18b20.c>
#include<ds1302.c>
#include<iic.c>
#include<key.c>
void main()
{
	banzi_init();
	Timer0Init();
	Timer1Init();
	EA = 1;
	ET0 = 1;
	DS1302_init();
	while(1)
	{
		ceju();
//		yi = juli / 100;
//		er = juli % 100 / 10;
//		san = juli % 10;
		
		wendu = DS18B20_Get();
//		yi = wendu / 10;
//		er = wendu % 10;
//		san = wenxiaoshu / 10;
		
		DS1302_write();
//		yi = shijian[2] / 10;
//		er = shijian[2] % 10;
//		san = 10;
//		si = shijian[1] / 10;
//		wu = shijian[1] % 10;
//		liu = 10;
//		qi = shijian[0] / 10;
//		ba = shijian[0] % 10;
		
		dianya = AD(0x03);
		dianya = dianya * 0.39;
		yi = dianya / 10;
		er = dianya % 10;
	//	xianshi();
	keyscan();
	if(kai == 1)
	{
		P2 = 0x80;
		P0 = 0xfe;
	}
//	else if(kai_1 == 1)
//	{
//		P2 = 0x80;
//		P0 = 0xf0;
//	}
	}
}	


