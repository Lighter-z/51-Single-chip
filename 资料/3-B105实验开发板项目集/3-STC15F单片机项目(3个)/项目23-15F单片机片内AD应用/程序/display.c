unsigned char seven_seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char cp2;
xdata ad_dat;
//xdata声明的变量（16位）存放在单片机的扩展RAM中，STC为片内256B以上的空间
//bdata声明的变量（16位）存放在单片机的0—128B空间，位可寻址，如：
//bdata BB;sbit BB_15 = BB^12;//BB_15是BB的某一位
sbit P1_0 = P1^0;
void display(void)
{
	switch(cp2)
	{
		case 0:	P1_0 = 0;P0 = 0x01;P1_0 = 1;P1_0 = 0;		//锁存位选，个位数码管阳极加高电平
				P0 = seven_seg[ad_dat % 10];break;			//P0输出个位
		case 1:	P1_0 = 0;P0 = 0x02;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = seven_seg[ad_dat % 100 / 10];break;	//P0输出十位	
		case 2:	P1_0 = 0;P0 = 0x04;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = seven_seg[ad_dat / 100 % 10];break;	//P0输出百位	
		case 3:	P1_0 = 0;P0 = 0x08;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = seven_seg[ad_dat / 1000];break;		//P0输出千位	
		/*
		case 4:	P1_0 = 0;P0 = 0x10;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = seven_seg[1];break;					//P0输出段选	
		case 5:	P1_0 = 0;P0 = 0x20;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = seven_seg[2];break;					//P0输出段选	
		case 6:	P1_0 = 0;P0 = 0x40;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = seven_seg[3];break;					//P0输出段选	
		case 7:	P1_0 = 0;P0 = 0x80;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = seven_seg[4];break;					//P0输出段选
		*/				
	}

}