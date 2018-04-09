//P0口驱动流水灯
//8个灯按顺序循环闪烁
//河南科技学院-单片机协会，2016年10月9日		 
#include<reg51.h>
unsigned char  LED[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//流水灯数组
void delay(unsigned int x)	//延时函数
{
	while(x--);
}
void main(void)				//主函数
{
	unsigned char i;	
	while(1)
	{
		P0 = LED[i];		//依次调用数组内数据
		delay(50000);		//延时
		i++;			    //循环1次，变量加1
		if(i >= 8)i = 0;	//到8清零
	}
}