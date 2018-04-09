//AD驱动，有关寄存器说明请参与STC15F手册
#include<intrins.h>
#define  nop    _nop_()

sfr ADC_CONTR = 0xbc;  	//AD控制寄存器
sfr ADC_RES = 0xbd;		//AD转换后数据存放高8位
sfr ADC_RESL = 0xbe;	//AD转换后数据存放低8位
sfr P1ASF = 0x9D;		//用于选择P1的8个端口为模拟口
sfr PCON2 = 0x97;		//时钟分频寄存器，这里只用的到PCON2中的ADRJ（转换换结果分配）

unsigned int get_ad(void)
{
	unsigned int i,j;
	P1ASF = 0x02;  								//设置P1.1为模拟输入端口，见手册P1ASF寄存器说明	
	PCON2 = PCON2 | 0x20;						//ADRJ  = 1;
	ADC_CONTR = 0x00;
	ADC_CONTR = ADC_CONTR | 0x80 | 0x40 | 0x01; //设置A/D电源开启|转换速度设置|输入端口P1.0；
												//见手册ADC_CONTR寄存器说明	
	nop;nop;nop;//等待电源稳定；
	ADC_CONTR = ADC_CONTR | 0x08;				//开始转换
	while((ADC_CONTR & 0x10) !=0x10); 			//等待转换标志置位
	i = ADC_RES;
	j = ADC_RESL;
	i = i << 8;
	i = i | j;
	ADC_CONTR = ADC_CONTR & ~0x10;		  		//清零转换标志位
	ADC_RES = 0x00;
	ADC_RESL = 0x00;
	return(i);
}