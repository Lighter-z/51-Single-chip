#include<reg51.h>
sfr CCON = 0xd8;				//可编程计数器PCA的控制寄存器
sfr CMOD = 0xd9;				//可编程计数器工作模式寄存器
sfr CL = 0xe9;					//可编程计数器的低八位
sfr CH = 0xf9;					//可编程计数器的高八位
/********PWM模块0，P1.1输出*********/
sfr CCAPM0 = 0xda;				//PWM功能寄存器			 
sfr CCAP0L = 0xea;				//高八位
sfr CCAP0H = 0xfa;				//低八位
sfr PCA_PMW0 = 0xf2;			//PWM辅助寄存器				  
/********PWM模块1，P1.0输出*********/
sfr CCAPM1 = 0xdb;
sfr CCAP1L = 0xeb;
sfr CCAP1H = 0xfb;
sfr PCA_PMW1 = 0xf3;
/********PWM模块2，P3.7输出********/
sfr CCAPM2 = 0xdc;
sfr CCAP2L = 0xec;
sfr CCAP2H = 0xfc;
sfr PCA_PMW2 = 0xf4;
void STC_pwm_init(void)
{
	CMOD = 0x0a;				//PWM频率 = 时钟频率 / 4 /256,若时钟频率为12M，则PWM波频率为11.7K；
	CL = 0x00;					//PCA计数器低8位清零
	CH = 0x00;					//PCA本计数器高8位清零
	/********PWM模块0，P1.1输出*********/
	PCA_PMW0 = 0x00;			//8位PMW，占空比的第九位EPC0L为0
	CCAPM0 = 0x42;				//允许比较，P1.1输出	
	/********PWM模块0，P1.0输出********/
	PCA_PMW1 = 0x00;			//8位PMW，占空比的第九位EPC0L为0
	CCAPM1 = 0x42;				//允许比较，P1.0输出
	/********PWM模块0，P3.7输出*********/
	PCA_PMW2 = 0x00;			//8位PMW，占空比的第九位EPC0L为0
	CCAPM2 = 0x42;				//允许比较，P3.7输出	
	CCON = 0x40;				//允许PAC计数，计数频率为时钟频率/4；
}

