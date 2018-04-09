unsigned char sec = 30,min = 30,hour = 12;
char sec_t,min_t,hour_t,hour_n,min_n;

unsigned char seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,
								0x92,0x82,0xf8,0x80,0x90};

unsigned char cp3,flash;
sbit P3_0 = P3^0;
void display(unsigned char x1,unsigned char x2)
{
	P3_0 = 0;
	P0 = x1;
	P3_0 = 1; 	
	P3_0 = 0;
	P0 = x2;
}
void dis_play0(void)
{
	switch(cp3)
	{
		case 0:display(0x80,seven_seg[sec % 10]);break;
		case 1:display(0x40,seven_seg[sec / 10]);break;
		case 2:display(0x20,0xbf | flash);break;
		case 3:display(0x10,seven_seg[min % 10]);break;
		case 4:display(0x08,seven_seg[min / 10]);break;
		case 5:display(0x04,0xbf | flash);break;
		case 6:display(0x02,seven_seg[hour % 10]);break;
		case 7:display(0x01,seven_seg[hour / 10]);break;
	}
}
void dis_play1(void)
{
	switch(cp3)
	{
		case 0:display(0x80,seven_seg[sec_t % 10]);break;
		case 1:display(0x40,seven_seg[sec_t / 10]);break;
		case 2:display(0x20,0xbf);break;
		case 3:display(0x10,seven_seg[min_t % 10]);break;
		case 4:display(0x08,seven_seg[min_t / 10]);break;
		case 5:display(0x04,0xbf);break;
		case 6:display(0x02,seven_seg[hour_t % 10] |flash);break;
		case 7:display(0x01,seven_seg[hour_t / 10] |flash);break;
	}
}
void dis_play2(void)
{
	switch(cp3)
	{
		case 0:display(0x80,seven_seg[sec_t % 10]);break;
		case 1:display(0x40,seven_seg[sec_t / 10]);break;
		case 2:display(0x20,0xbf);break;
		case 3:display(0x10,seven_seg[min_t % 10] |flash);break;
		case 4:display(0x08,seven_seg[min_t / 10] |flash);break;
		case 5:display(0x04,0xbf);break;
		case 6:display(0x02,seven_seg[hour_t % 10]);break;
		case 7:display(0x01,seven_seg[hour_t / 10]);break;
	}
}
void dis_play3(void)
{
	switch(cp3)
	{
		case 0:display(0x80,seven_seg[sec_t % 10] |flash);break;
		case 1:display(0x40,seven_seg[sec_t / 10] |flash);break;
		case 2:display(0x20,0xbf);break;
		case 3:display(0x10,seven_seg[min_t % 10]);break;
		case 4:display(0x08,seven_seg[min_t / 10]);break;
		case 5:display(0x04,0xbf);break;
		case 6:display(0x02,seven_seg[hour_t % 10]);break;
		case 7:display(0x01,seven_seg[hour_t / 10]);break;
	}
}
void dis_play4(void)
{
	switch(cp3)
	{
		case 0:display(0x80,seven_seg[min_n % 10] );break;
		case 1:display(0x40,seven_seg[min_n / 10] );break;
		case 2:display(0x20,0xbf);break;
		case 3:display(0x10,seven_seg[hour_n % 10]|flash);break;
		case 4:display(0x08,seven_seg[hour_n / 10]|flash);break;
		case 5:display(0x04,0xbf);break;
		case 6:display(0x02,seven_seg[0]);break;
		case 7:display(0x01,0xc8);break;
	}
}
void dis_play5(void)
{
	switch(cp3)
	{
		case 0:display(0x80,seven_seg[min_n % 10] |flash);break;
		case 1:display(0x40,seven_seg[min_n / 10] |flash);break;
		case 2:display(0x20,0xbf);break;
		case 3:display(0x10,seven_seg[hour_n % 10]);break;
		case 4:display(0x08,seven_seg[hour_n / 10]);break;
		case 5:display(0x04,0xbf);break;
		case 6:display(0x02,seven_seg[0]);break;
		case 7:display(0x01,0xc8);break;
	}
}