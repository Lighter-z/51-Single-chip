#include<reg51.h>									   
#include<DS18B20.c>
code uchar seven_seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar cp2;
uint aa,cp1;
uint temp_num,temp_num1,temp_dot,temp;
sbit P1_0=P1^0;
void timer0_isr()interrupt 1	   //中断服务函数
{
	TH0 = (65536-2000)/256;			  //TH0重置函数
	TL0 = (65536-2000)%256;			  //TL0重置函数
	cp1++;
	if(cp1>=500)					  //1秒
	{
		cp1 = 0;
		temp_num = Read_Temperature();			  //将读取到的温度赋值给temp_num
		temp_dot = c * 0.625;					   //得到温度的小数
		if((temp_num&0x80)==0x80)				  //如果温度为负值
		{
			temp_dot = (0x0f-c)*0.625;			  //补码转换原码，小数处理
			temp_num1 = 0xff - temp_num;		  //补码转换原码，整数处理
		}
		else temp_num1 = temp_num;				  //小数转换为十进制
	}
	P0 = 0xff;									  //消隐
	switch(cp2)
	{
		case 0:P1_0 = 0;P0 = 0x01;P1_0 = 1;P1_0 = 0;
		P0 = seven_seg[temp_dot];break;	      //显示小数
		case 1:P1_0 = 0;P0 = 0x02;P1_0 = 1;P1_0 = 0;
		P0 = 0x7f&seven_seg[temp_num1%10];break;	//显示个位并加小数点
		case 2:
		{
			if(temp_num<10)break;	 //如果温度小于10度，且不为负值，十位0不显示
			if((temp_num>0x80)&&(temp_num1<10))	 //如果温度小于10度，并为负值，十位0不显示，只显示——
			{
				P1_0 = 0;P0 = 0x04;P1_0 = 1;P1_0 = 0;
				P0 = 0xbf;break;
			}
			P1_0 = 0;P0 = 0x04;P1_0 = 1;P1_0 = 0;//如果温度大于10度，十位正常显示
			P0=seven_seg[temp_num1/10];
			break;
		}	  
		case 3:
		{
			if((temp_num>0x80)&&((temp_num1/10)>0))	   //如果为负值，且十位不为0，百位显示——
			{
				P1_0 = 0;P0 = 0x08;P1_0 = 1;P1_0 = 0;
				P0 = 0xbf;
				break;	
			}
		}
	}
	cp2++;
	if(cp2>=4)cp2 = 0;		
}
void timer0_init()
{
	TMOD = 0x01;					   //方式一
	TH0 = (65536-2000)/256;			   //TH0 预置，65536十六进制低8位。
	TL0 = (65536-2000)%256;			   //TL0 预置，65536十六进制高8位。
	EA = 1;							   //终端总开关打开
	TR0 = 1;						   //定时计数器T0的起停控制位打开
	ET0 = 1;						   //定时计数器T0的中断端控制位打开
}
void main()
{
	timer0_init();
	write_temprom(128,-55);	//向18B20的暂存写上、下限温度分别为128，-55
	Write_OneChar(0x48);	//向18B20的rom中写数据		
	while(1);
	//{
	//	temp = read_temprom;	//从DS18B20中读取的温度给变量temp 
	//}
}