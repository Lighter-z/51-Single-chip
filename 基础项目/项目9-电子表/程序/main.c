#include<reg51.h>
#include<DEFINE.c>
#include<KEY.c>
#include<DISPLAY.c>
void timer_isr()interrupt 1			  //中断服务函数
{
	TL0 = (65536-2000) %256;			  //TL0重置函数
	TH0 = (65536-2000)/256;			  //TH0重置函数
	cp++;
	if(cp>=250)       //0.5s
	{
		cp1++;
		cp = 0;
		flash = ~flash;        //0.5s  - 闪烁
		if(cp1>=2)    //1s
		{
			if(mode==0)		   //调整时，时间停止
			sec++;
			cp1 = 0;
			if(sec>=60)     //1min
			{
				min++;
				sec = 0;
				if(min>60)	 //1h
				{
					hour++;
					min = 0;
					if(hour>=24)hour = 0;
				}
			}
		}
	}
	P0 = 0xff;    //消隐
	switch(mode)
	{
		case 0:dis_play0();break;  //正常
		case 1:dis_play1();break;  //调时
		case 2:dis_play2();break;  //调分
		case 3:dis_play3();break;  //调秒
		case 4:dis_play4();break;  //调闹时
		case 5:dis_play5();break;  //调闹分
	}
	i++;
	if(i>=8)i = 0;	
}
void timer0_init()				   //中断初始化函数
{
	TMOD = 0x01;				  //方式一
	TL0 = (65536-2000)%256;		  //TL0 预置，65536十六进制低8位。
	TH0 = (65536-2000)/256;		  //TH0 预置，65536十六进制高8位。
	EA = 1;							//CPU中断开放 ，总中断打开
	ET0 = 1;						//定时计数器T0的溢出终端控制位，T0中断打开
	TR0 = 1;						//定时计数器T0的启停控制位，启动T0
}
void main()
{
	timer0_init();				   //timer0初始化，为中断做准备
	while(1)
	{
		key();
		if(hour == hour_n && min == min_n)	   //闹钟到时间，蜂鸣器响
		{
			P3_2 = !P3_2;
			delay(50);
		}
	}
}