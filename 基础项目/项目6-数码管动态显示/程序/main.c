#include<reg51.h>
sbit P1_0=P1^0;
code unsigned char seven_seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,
									0x82,0xf8,0x80,0x90};
void delay(unsigned char x)
{
	while(x--);
}										
void display()
{
	unsigned char i;
	P0=0xff;//消影
	switch(i)
	{
		case 0:P1_0=0;P1_0=1;P0=0x01;P1_0=0;P0=seven_seg[1];break;//P0=0x01 开位选   P1_0=0;P0=seven_seg[1]开段选
		case 1:P1_0=0;P1_0=1;P0=0x02;P1_0=0;P0=seven_seg[1];break;
		case 2:P1_0=0;P1_0=1;P0=0x04;P1_0=0;P0=seven_seg[2];break;
		case 3:P1_0=0;P1_0=1;P0=0x08;P1_0=0;P0=seven_seg[3];break;
		case 4:P1_0=0;P1_0=1;P0=0x10;P1_0=0;P0=seven_seg[4];break;
		case 5:P1_0=0;P1_0=1;P0=0x20;P1_0=0;P0=seven_seg[5];break;
	}
	i++;
	if(i>=6)i=0;
}
void main()
{  
	while(1)
	{
	 	display();
		delay(50);
	}
}