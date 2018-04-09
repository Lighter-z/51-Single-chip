#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
#include<LCD1602.c>
void main()
{
	uchar i,sec = 56;
	FLCD1602_init();
	FLCD1602_clear();
	while(1)
	{
		FLCD1602_clear();
		display_string("How are you");
		gotoxy(2,0);
		display_string("dat:2012/09/01");
		delay(50000);delay(50000);delay(50000);delay(50000);
		FLCD1602_clear();
		display_string("Time:");display_num(sec);display_string(" ");display_num(i);
		gotoxy(2,0);
		display_string("end");
		delay(50000);delay(50000);delay(50000);delay(50000);
		i++;
		if(i>100)i = 0;
	}
}