#include<reg51.h>
#include<lcd12864.c>
uchar sec = 59;
void main(void)
{
	F12864_init();
	F12864_clear();
	while(1)
	{
		sec++;
		if(sec >= 60)sec = 0;
		dprintf_hanzi_string_1(GB_16,1,16,6,0);			//左右移动8点阵，上下为1
		display_string(5,7,"sec");						 //5表示横向8点阵倍数，7也是8点阵的倍数
		display_num(5,6,sec);display_string(7,6,":");							
	}
}