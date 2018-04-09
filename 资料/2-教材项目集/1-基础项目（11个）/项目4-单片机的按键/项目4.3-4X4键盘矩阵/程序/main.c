//4*4键盘矩阵按键，针对教材设计
//按键按下显示键值，不按显示"88"
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#define uchar unsigned char
code P1_scan[]={0x7f,0xbf,0xdf,0xef};
code key_temp_value[]={0xee,0xed,0xeb,0xe7,
					   0xde,0xdd,0xdb,0xd7,
					   0xbe,0xbd,0xbb,0xb7,
					   0x7e,0x7d,0x7b,0x77};
code uchar seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar n = 88;
void delay(uchar x)
{
	while(x--);
}
uchar key_scan(void)
{
	uchar i,j;
	for(i = 0;i < 4;i++)							//让键盘行线输出扫描数据
	{
		P1 = P1_scan[i];
		if(P1 != P1_scan[i])
		{
			delay(200);								//消除键抖后，有按键确实按下
			if(P1 != P1_scan[i])					//如果有按键按下，P1口不是原来的扫描数据
			{
				for(j = 0;j < 16;j++)
				{
					if(P1 == key_temp_value[j])		//判断键值，是哪个按键按下
					n = j;							//返回按键的编号
				}
			}
		}
	}
	return (n);										//如果没有按键按下，输出标志"88"
}
void display(uchar i)								//显示函数
{
	P2 = ~0x01;P0 = seven_seg[i % 10];				//显示按键编号个位
	delay(300);										//让个位显示一段时间
	P2 = ~0x02;P0 = seven_seg[i / 10];				//显示按键编号十位
	delay(300);										//让十位显示一段时间
	P0 = 0xff;										//刷新P0接口（消隐）
}
void main()
{
	uchar i;
	while(1)
	{
		i = key_scan();
		display(i);
	}
}