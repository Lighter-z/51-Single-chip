#include<reg51.h>
code unsigned char  LED[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};	   //流水灯数组
void delay(unsigned int x)	  //延时函数
{
	while(x--);
}
void main()
{
	unsigned char i;
	while(1)
	{
	P0 = LED[i];		  //调用数组内的数据
	delay(5000);		 //延时
	i++;				//循环一次，变量i加1
	if(i>=8)i=0;	   //i=8，清零
	}

}