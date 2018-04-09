#include<reg51.h>
code unsigned char seven_seg[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,
			0x82,0xf8,0x80,0x90};
unsigned char i,cp;
/*timer0的中断服务函数*/
void timer0_isr()interrupt 1	  	//中断服务函数
{
	TL0 = (65536-5000)%256;			//TL0重置函数
	TH0 = (65536-5000)/256;			//TH0重置函数
	cp++;							//每次触发中断，cp加一
	if(cp>=200)				  //200次，1s
	{
		i++;
		cp = 0;
	}
		if(i>=10)i=0;
		P0=seven_seg[i];
		
}
void timer0_init()	             //中断初始化函数
{
	TMOD = 0x01;		    	 //方式一
	TL0 = (65536-5000)%256;		 //TL0 预置，65536十六进制低8位。
	TH0 = (65536-5000)/256;		 //TH0 预置，65536十六进制高8位。
	EA = 1;						 //总中断开放
	ET0 = 1;					//T0中断打开
	TR0 = 1;					 //启动定时计数器T0
}
void main()
{
	timer0_init();				//timer_0初始化,为中断做好准备
	while(1);
}	   