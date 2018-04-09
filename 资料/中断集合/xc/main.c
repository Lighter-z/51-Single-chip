/**2016年5月24日**/
/**孙宇博**/
/**此程序用到了中断号0,1,2,3，**/
/**当外部中断0处于低电平状态，定时器/计数器T0停止计时。高电频时恢复计时（采用按键方式来调整高低电平)**/
/**当外部中断1处于低电平状态，定时器/计数器T1停止计时。高电频时恢复计时（采用按键方式来调整高低电平)**/
/**当外部中断0按键按下时加一，当外部中断1按键按下时减一**/
#include <reg51.h>
unsigned char i,sec,sec1,cp2;
unsigned int cp1,cp3; 

unsigned char seven_seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

//void delay(unsigned int x)
//{while(x--);}

void isr0() interrupt 0
{
	i++;
	if(i>=99)
	i=99;
}
void isrT0() interrupt 1
{
//	TH0  = (65536 - 2000)/256; //T0 由外部中断0控制
//	TL0  = (65536 - 2000)%256; //T0 由外部中断0控制

	TH0  = 0; //T0 由外部中断0控制
	TL0  = 0; //T0 由外部中断0控制

	cp1++;
	if(cp1>=50)
	{
		sec ++;
		if(sec==99)
		sec=0;
		cp1= 0;	
	}
}

void isr2() interrupt 2
{
	i--;
	if(i<=0)
	i=0;
}

void isrT1() interrupt 3
{
	TH1 = (65536 - 2000)/256; //T1 高位溢满计数 
	TL1 = (65536 - 2000)%256; //T1 高位溢满计数
	cp3++;
	if(cp3>=500)
	{
		sec1 ++;
		if(sec1==99)
		sec1=0;
		cp3= 0;	
	}
}



void init0()
{		
	TMOD = 0x99;
//	TH0  = (65536 - 2000)/256; //T0 由外部中断0控制
//	TL0  = (65536 - 2000)%256; //T0 由外部中断0控制

	TH0  = 0; //T0 由外部中断0控制
	TL0  = 0; //T0 由外部中断0控制

	TH1  = (65536 - 2000)/256; //T1 由外部中断1控制
	TL1  = (65536 - 2000)%256; //T1 由外部中断1控制

	EA   = 1;//cpu中断开放  但每个中断源的中断请求是允许还是禁止，还需要各自的控制位调整

	INT1 = 1;
	IT1  = 1;//外部中断1的触发控制位
	EX1  = 1;//外部中断1的中断控制位，允许外部中断1开放 P3^3
	TR1  = 1;//是T1的控制位
	ET1  = 1;//是计数器T1的溢出中断控制位

	INT0 = 1;
	IT0  = 1;//外部中断0的触发控制位
	EX0  = 1;//外部中断0的中断控制位，允许外部中断0开放 P3^2
	TR0  = 1;//是T0的控制位
	ET0  = 1;//是计数器T0的溢出中断控制位
}

void display()
{
	P0 = 0xff;
	switch (cp2)
	{
		case 0:P2=~0x01;P0 = seven_seg[i%10];break;
		case 1:P2=~0x02;P0 = seven_seg[i/10];break;
		case 2:P2=~0x04;P0 = seven_seg[sec1%10];break;
		case 3:P2=~0x08;P0 = seven_seg[sec1/10];break;
		case 4:P2=~0x10;P0 = seven_seg[sec%10];break;
		case 5:P2=~0x20;P0 = seven_seg[sec/10];break;
		
	}
	cp2++;
	if(cp2>=6)cp2=0;
}

void main()
{
	init0();

	while(1)
	{
		display();
	}		
}


