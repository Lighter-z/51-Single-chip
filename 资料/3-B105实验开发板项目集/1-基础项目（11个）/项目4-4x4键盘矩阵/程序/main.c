//4*4键盘矩阵按键
//按键按下显示键值，不按显示“88”
//河南科技学院-单片机协会，2016年10月9日		 
#include<reg51.h>
sbit P3_0 = P3^0;
code unsigned char seven_seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,
									0x92,0x82,0xf8,0x80,0x90,};
code unsigned char key_scan[] = {0xef,0xdf,0xbf,0x7f,};
code unsigned char key_num[] = 	{
									0xee,0xed,0xeb,0xe7,
									0xde,0xdd,0xdb,0xd7,
									0xbe,0xbd,0xbb,0xb7,
									0x7e,0x7d,0x7b,0x77,
								}; //按键按下的键值

void delay(unsigned int x)					//延时函数
{
	while(x--);
}
void display(unsigned char x)				//显示函数
{	
	P0 = 0xff;								//刷新P0口（消隐）
	P3_0 = 0;P0 = 0x01;P3_0 = 1;P3_0 = 0;
	P0 = seven_seg[x % 10];					//显示按键编号的个位
	delay(300);								//让个位显示一段时间
	P0 = 0xff;									//刷新P0口（消隐）
	P3_0 = 0;P0 = 0x02;P3_0 = 1;P3_0 = 0;
	P0 = seven_seg[x / 10];					//显示按键编号的十位
	delay(300);								//让十位显示一段时间
}
unsigned char key(void)						//按键函数
{
	unsigned char i,j;
	for(i = 0;i < 4;i++)
	{
		P2 = key_scan[i];
		if(P2 != key_scan[i])
		{
			delay(500);							//消除键抖后，有按键确实按下
			if(P2 != key_scan[i]);				//如果有按键按下，P2口不是原来扫描数据
			for(j = 0;j < 16;j++)				//让键盘行线输出扫描数据
			{
				if(P2 == key_num[j])return(j);	//判断键值,返回按键的编号				
			} 
		}
	}
	return(88);			//如果没有按键按下，输出标准"88"
}
void main(void)			//主函数
{
	unsigned char k;
	while(1)
	{
		k = key();
		display(k);
	}			
}