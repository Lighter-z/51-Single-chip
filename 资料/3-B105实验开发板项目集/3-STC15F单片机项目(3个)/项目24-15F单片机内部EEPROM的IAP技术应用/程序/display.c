code uchar seven_seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar cp2;
xdata uchar	 hour = 12,min = 30,sec = 30;					//定时器产生的时间变量

sbit P1_0 = P1^0;
xdata uchar	 flash,hour_c,min_c,sec_c;						//从存储器读的临时数据
void display(void)
{
	switch(cp2)
	{
		case 0:	P1_0 = 0;P0 = 0x01;P1_0 = 1;P1_0 = 0;		//锁存位选，个位数码管阳极加高电平
				P0 = seven_seg[sec % 10];break;				//P0输出秒个位段选
		case 1:	P1_0 = 0;P0 = 0x02;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = seven_seg[sec / 10];break;				//P0输出秒十位	
		case 2:	P1_0 = 0;P0 = 0x04;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = 0xbf  | flash;break;					//P0输出闪烁的"-"	
		case 3:	P1_0 = 0;P0 = 0x08;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = seven_seg[min % 10];break;				//P0输出分钟的个位
		case 4:	P1_0 = 0;P0 = 0x10;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = seven_seg[min / 10];break;				//P0输出分钟的十位
		case 5:	P1_0 = 0;P0 = 0x20;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = 0xbf  | flash;;break;					//P0输出闪烁的"-"	
		case 6:	P1_0 = 0;P0 = 0x40;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = seven_seg[hour % 10];break;			//P0输出小时的个位	
		case 7:	P1_0 = 0;P0 = 0x80;P1_0 = 1;P1_0 = 0;		//锁存位选
				P0 = seven_seg[hour / 10];break;			//P0输出小时的十位
						
	}

}