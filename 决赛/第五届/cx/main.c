#include<stc15f2k60s2.h>
#include<define.c>
#include<ds18b20.c>
#include<iic.c>
#include<ds1302.c>
#include<key.c>

void send(unsigned char *p)
{
	unsigned char i = 0;
	do
	{
		SBUF = p[i++];
		while(TI == 0);
		TI = 0;
	}
	while(p[i] != 0);
}

void UartInit(void)		//1200bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0x00;		//设定定时初值
	TH1 = 0xF7;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

void uart()interrupt 4
{
	RI = 0;
	num = SBUF;
	if(flag_num == 0)
	{
		if(num == 'A')
		{
			flag_num = 1;
		}
	}
	else if(flag_num == 1)
	{
		if(num == 'A')
		{
			flag_num = 2;
		}
	}
	else if(flag_num == 2)
	{
		if(num == 'A')
		{
			flag_num = 3;
		}
	}
	else if(flag_num == 3)
	{
		if(num == 'S')
		{
			flag_num = 4;
		}
	}
		else if(flag_num == 4)
	{
		if(num == 'S')
		{
			flag_num = 5;
		}
	}
		else if(flag_num == 5)
	{
		if(num == 'S')
		{
			flag_num = 0;
			mimadui = 1;
		}
	}
}

void display()
{
	if(line >= 200)
	{
		ren = 0;
		P2 = 0x80;
		P0 &= 0xff;
		if(t == 1)
		{
			t = 0;
			max = shijian[0];		
			if(max > min)
			{
				tingshi = max - min;
			}
			else 
			{
				tingshi = min - max;
			}
				IIc_Write(add,wendu);Delay1ms();Delay1ms();add++;
			IIc_Write(add,shidu);Delay1ms();Delay1ms();add++;
			IIc_Write(add,shijian[2]);Delay1ms();Delay1ms();add++;
			IIc_Write(add,shijian[1]);Delay1ms();Delay1ms();add++;
			IIc_Write(add,shijian[0]);Delay1ms();Delay1ms();add++;
			IIc_Write(add,tingshi);Delay1ms();Delay1ms();add++;
					if(add == 0x23)add = 0x00;
		}
	}
	else 
	{
		ren = 1;
		P2 = 0x80;
		P0 &= 0xfb;
		if(t == 0)
		{
			t = 1;
			min = shijian[0];
		}
	}
	if(s5 == 0)
	{
		yi = wendu / 10;
		er = wendu % 10;
		san = 12;
		si = 10;	
		wu = 10;
		liu = shidu / 10;
		qi = shidu % 10;
		ba = 13;
	}
	else if(s5 == 1)
	{
		yi = shijian[2] / 10;
		er = shijian[2] % 10;
		san = 11;
		si = shijian[1] / 10;
		wu = shijian[1] % 10;
		liu = 11;
		qi = shijian[0] / 10;
		ba = shijian[0] % 10;	
	}
	else if(s5 == 2)
	{
		if(ren == 1)
		{
			yi = 10;
			er = 10;
			san = 10;
			si =  11;
			wu = 0;
			liu = 0;
			qi = 0;
			ba = 0;
		}
		else if(ren == 0)
		{
			yi = 10;
			er = 10;
			san = 10;
			si =  11;
			wu = 0;
			liu = 0;
			qi = tingshi / 10;
			ba = tingshi % 10;
		}
	}
}	

void xinxi()
{
	if(moshi == 0)
	{
		P2 = 0x80;
		P0 &= 0xfe;
		if(last_time != shijian[0])
		{
			last_time = shijian[0];
			if(mimadui == 1)
			{
				sprintf((char *)chuankou,"{%bd-%bd%%}{%0.2bd-%0.2bd-%0.2bd}{%bd}\r\n",wendu,shidu,shijian[2],shijian[1],shijian[0],ren);
				send(chuankou);
			}
		}
	}
	else if(moshi == 1)
	{
		P2 = 0x80;
		P0 &= 0xfd;
		if(mimadui == 1)
		{
			mimadui = 0;add = 0x00;
			for(i = 0;i <= 5;i++)
			{
				wendu = IIc_Read(add);Delay1ms();Delay1ms();add++;
				shidu = IIc_Read(add);Delay1ms();Delay1ms();add++;
				shijian[2] = IIc_Read(add);Delay1ms();Delay1ms();add++;
				shijian[1] = IIc_Read(add);Delay1ms();Delay1ms();add++;
				shijian[0] = IIc_Read(add);Delay1ms();Delay1ms();add++;
				tingshi = IIc_Read(add);Delay1ms();Delay1ms();add++;
				sprintf((char *)chuankou,"{%bd-%bd%%}{%0.2bd-%0.2bd-%0.2bd}{%bd}\r\n",wendu,shidu,shijian[2],shijian[1],shijian[0],tingshi);
				send(chuankou);
			}
		}
	}
}

void main()
{
	EA = 1;
	ES = 1;
	banzi_init();
	UartInit();
	DS1302_init();
	while(1)
	{
		wendu = DS18B20();
		shidu = AD(0x03);shidu = AD(0x03);
		line = AD(0x01);line = AD(0x01);
		DS1302_read();
		keyscan();
		shidu = shidu * 0.39;
		display();
		 xinxi();
		xianshi();
	}
}