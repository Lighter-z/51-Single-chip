#include<intrins.h>
#define uchar unsigned char 
#define nop  _nop_()
sbit CS = P3^0;
sbit CLK = P3^1;
sbit DIDO = P3^2;
/*对ADC0832初始化处理*/
void adc0832_init(void)
{
	CS = 1;nop;	                              
	CLK = 1;
	CS = 0;
}
/*对转换ch0通道的模拟信号*/
uchar adc0832_ch0(void)
{
	uchar dat1,i;
	adc0832_init();
	DIDO = 1;CLK = 0;nop;CLK = 1;nop;		  //第一个下降沿，DI必须为高电平，表示启始信号
	DIDO = 1;CLK = 0;nop;CLK = 1;nop;		  //第二个下降沿
	DIDO = 0;CLK = 0;nop;CLK = 1;nop;	      //第三个下降沿，发送1,0；选择通道ch0
	DIDO = 1;								  //释放总线
	for(i = 0;i<8;i++)						  //第4个下降沿到第11个下降沿
	{										 
		CLK = 0;nop;						  //
		if(DIDO)dat1 = dat1|0x01;			  //最低位置1
		CLK = 1;nop;						  //
		dat1 = dat1<<1;						  //左移，依次输出最高位
	}
	return(dat1);
	CS = 1;
}