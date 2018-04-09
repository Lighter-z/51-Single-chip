//数字温度传感器应用，教材和B105型实验开发板通用
//实时读取并且显示温度
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#include<ds18b20.c>	
sbit P1_0 = P1^0;	
code  uchar seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};			//共阳极数码管数显编码
uchar cp1,cp2;
uint aa;
uint temp_num,temp_num1,temp_dot,temp;													//temp_num、temp_num1为温度整数部分，temp_dot小数部分，中间变量temp
void timer0_init(void)																	//中断服务函数	 
{
	TMOD = 0x01;
	TH0 = (65536 - 2000) / 256;
	TL0 = (65536 - 2000) % 256;
	TR0 = 1;
	EA  = 1;
	ET0 = 1;
}
void timer0_isr(void) interrupt 1														//中断服务函数		  	
{
	TH0 = (65536 - 2000) / 256;
	TL0 = (65536 - 2000) % 256;
	cp1++;
	if(cp1 >= 250)                              										//1秒
   {
		cp1 = 0;
		temp_num = Read_Temperature();													//得到温度整数
		temp_dot =  c * 0.625;															//得到温度小数
		if((temp_num & 0x80) == 0x80)													//如果温度为负值
		{	
			temp_dot = (0x0f - c) * 0.625;												//补码转换原码，小数处理
			temp_num1 = 0xff - temp_num;												//补码转换原码，整数处理	
		}
		else temp_num1 = temp_num;														//小数转换为十进制
	}
	P0 = 0xff;
	switch(cp2)
	{
		case 0: P0 = 0xff;																//消隐
				P1_0 = 0;P0 = 0x01;P1_0 = 1;P1_0 = 0;
				P0 = seven_seg[temp_dot]; break;										//小数部分显示
		case 1: P0 = 0xff;
				P1_0 = 0;P0 = 0x02;P1_0 = 1;P1_0 = 0;
				P0 = 0x7f & seven_seg[temp_num1 % 10%10]; break;						//整数部分各位显示
		case 2:
			{	
				if(temp_num < 10)
				{
					P0 = 0xff;
					P1_0 = 0;P0 = 0x04;P1_0 = 1;P1_0 = 0;
					P0 = 0xff; break;
				}																		//如果温度小于10度，且为正值，十位0不显示
				if((temp_num > 0x80) && ( temp_num1 < 10))
				{
					P0 = 0xff;
					P1_0 = 0;P0 = 0x04;P1_0 = 1;P1_0 = 0;
					P0 = 0xbf; break;
				}																		//如果温度小于10度，且为负值，十位0不显示，只显示"-"
					P0 = 0xff;
					P1_0 = 0;P0 = 0x04;P1_0 = 1;P1_0 = 0;
					P0 = seven_seg[temp_num1 / 10%10]; break;							//如果温度大于10度，10位正常显示
			}
		case 3:
			{
				if((temp_num < 0x80) && (temp_num1 >= 100))
				{		
					P0 = 0xff;
					P1_0 = 0;
					P0 = 0x08;
					P1_0 = 1;
					P1_0 = 0;
					P0 = seven_seg[temp_num1 / 100]; break;								//如果温度为负值，且十位不为0，百位显示"-"
				}
			
			}
	 	case 4:
			{
				if((temp_num > 0x80) && ((temp_num1 / 10) > 0))
				{
					P0 = 0xff;
					P1_0 = 0;P0 = 0x08;P1_0 = 1;P1_0 = 0;
					P0 = 0xbf; break;													//如果温度为负值，且十位不为0，百位显示"-"
				}
			}
	}
	cp2++;
	if(cp2 >= 5)
	cp2=0;
}
void main(void)	
{
	timer0_init();
	write_temprom(128,-55);																//向18B20的暂存写上、下限温度分别为128，-55
	Write_OneChar(0x48);																//向18B20的rom中写数据		
	while(1)
	{
	 	temp = read_temprom;															//将从DS18B20中读取的温度给变量temp 
	}
}
