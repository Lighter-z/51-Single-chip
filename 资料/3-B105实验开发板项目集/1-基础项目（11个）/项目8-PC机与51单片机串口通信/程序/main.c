//串口通信
//计算机通过串口调试助手向实验开发板发送一个数据，开发板接收后返回这个数据
//河南科技学院-单片机协会，2016年10月9日		 
#include<reg51.h>
void s_init(void)
{
	SCON = 0x50;	//设置串口通信控制寄存器，工作方式1，允许串口接收数据
	TMOD = 0x20;	//设定定时器T1，工作方式2，自动装初值
	TH1 = 0xfd;		//设定波特率为9600bps，工作方式2，自动装初值，9600
	TL1 = 0xfd;
	TR1 = 1;
}
void main(void)
{
	unsigned char i;
	s_init(); 
	P0 = 0x00;		//初始化LED灯
	while(1)
	{
		while(!RI);	//等待接收
		i = SBUF;	//接收的数据给i	
		//P0 = i;	//通过发送的数据控制LED灯	
		RI = 0;		//RI软件清零
		SBUF = i;	//返回单片机接受的数据
		while(!TI);	//等待发送
		TI = 0;		//TI软件清零
	}
}