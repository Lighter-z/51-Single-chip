#include<intrins.h>
#define nop _nop_();
#define uchar unsigned char
#define uint unsigned int
sbit CS = P3^0;									//特殊位定义 即CS片选信号接在P3.0端口
sbit CLK = P3^1;								//特殊位定义 即CLK时钟信号接在P3.1端口
sbit DIDO = P3^2;								//特殊位定义 即数据选通信号接在P3.2端口
/**********ADC0832初始化函数***********/
void dac0832_init(void)
{
	CS = 1;_nop_();
	CLK = 1;
	CS = 0;	
}
/*****对转换CH0通道的模拟信号函数******/
uchar dac0832_ch0(void)//包含11个CLK下降沿
{		
	uchar i,dat1;
	dac0832_init();
	DIDO = 1;CLK = 0;nop;CLK = 1;nop;			//SCK第1个下降沿来到时，DI = 1启动DAC0832
	DIDO = 1;CLK = 0;nop;CLK = 1;nop;			//SCK第2个下降沿
	DIDO = 0;CLK = 0;nop;CLK = 1;nop;			//SCK第3个下降沿,发送1、0选择通道ch0
	DIDO = 1;									//释放总线 
	for(i = 0;i < 8;i++)						//SCK第4个下降沿到第11个下降沿,
	{	
		CLK = 0;nop;
		if(DIDO)dat1 = dat1 | 0x01;
		CLK = 1;nop;
		dat1 = dat1 << 1;
	}
		return(dat1);
		CS = 1;	
}