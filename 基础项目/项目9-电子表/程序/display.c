void display(unsigned char x1,x2)
{
	P3_0 = 0;	  //锁存器关
	P0 = x1;	  //输入位选			 
	P3_0 = 1;	  //锁存器开
	P3_0 = 0;	  //锁存器关
	P0 = x2;	  //输入段选		
}
void dis_play0()			  //mode = 0 正常  显示
{
	switch(i)
	{
		case 0:display(0x01,seven_seg[sec%10]);break;	  //显示秒个位
		case 1:display(0x02,seven_seg[sec/10]);break;	  //显示秒十位
		case 2:display(0x04,0xbf|flash);break;			  //显示 -	  闪烁
		case 3:display(0x08,seven_seg[min%10]);break;	  //显示分个位
		case 4:display(0x10,seven_seg[min/10]);break;	  //显示分十位
		case 5:display(0x20,0xbf|flash);break;			  //显示 -    闪烁
		case 6:display(0x40,seven_seg[hour%10]);break;	  //显示时个位
		case 7:display(0x80,seven_seg[hour/10]);break;	  //显示时十位
	}
}
void dis_play1()			  //mode = 1 调时
{
	switch(i)
	{
		case 0:display(0x01,seven_seg[sec_t%10]);break;	  //显示调秒个位
		case 1:display(0x02,seven_seg[sec_t/10]);break;	  //显示调秒十位
		case 2:display(0x04,0xbf);break;				  //显示 -
		case 3:display(0x08,seven_seg[min_t%10]);break;	  //显示调分个位
		case 4:display(0x10,seven_seg[min_t/10]);break;	  //显示调分十位
		case 5:display(0x20,0xbf);break;				  //显示 -
		case 6:display(0x40,seven_seg[hour_t%10]|flash);break;	 //显示调时个位	   闪烁
		case 7:display(0x80,seven_seg[hour_t/10]|flash);break;	 //显示调时十位	   闪烁
	}
}
void dis_play2()			  //mode = 2 调分
{
	switch(i)
	{
		case 0:display(0x01,seven_seg[sec_t%10]);break;	  //显示调秒个位
		case 1:display(0x02,seven_seg[sec_t/10]);break;	  //显示调秒十位
		case 2:display(0x04,0xbf);break;				  //显示  -
		case 3:display(0x08,seven_seg[min_t%10]|flash);break;	  //显示调分个位   闪烁
		case 4:display(0x10,seven_seg[min_t/10]|flash);break;	  //显示调分十位   闪烁
		case 5:display(0x20,0xbf);break;						  //显示 -
		case 6:display(0x40,seven_seg[hour_t%10]);break;		  //显示调时个位
		case 7:display(0x80,seven_seg[hour_t/10]);break;		  //显示调时十位
	}
}
void dis_play3()			  //mode = 3 调秒
{
	switch(i)
	{
		case 0:display(0x01,seven_seg[sec_t%10]|flash);break;	  //显示调秒个位  闪烁
		case 1:display(0x02,seven_seg[sec_t/10]|flash);break;	  //显示调秒十位  闪烁
		case 2:display(0x04,0xbf);break;						  //显示 -
		case 3:display(0x08,seven_seg[min_t%10]);break;			  //显示调分个位
		case 4:display(0x10,seven_seg[min_t/10]);break;			  //显示调分十位
		case 5:display(0x20,0xbf);break;						  //显示 -
		case 6:display(0x40,seven_seg[hour_t%10]);break;		  //显示调时个位
		case 7:display(0x80,seven_seg[hour_t/10]);break;		  //显示调时十位
	}
}		
void dis_play4()			  //mode = 4 调闹时
{
	switch(i)
	{
		case 0:display(0x01,0xbf);break;						  //显示 -
		case 1:display(0x02,0xbf);break;						  //显示 -
		case 2:display(0x04,0xbf);break;						  //显示 -
		case 3:display(0x08,seven_seg[min_n%10]);break;			  //显示闹分个位
		case 4:display(0x10,seven_seg[min_n/10]);break;			  //显示闹分十位
		case 5:display(0x20,0xbf);break;						  //显示 -
		case 6:display(0x40,seven_seg[hour_n%10]|flash);break;	  //显示闹时个位    闪烁
		case 7:display(0x80,seven_seg[hour_n/10]|flash);break;	  //显示闹时十位    闪烁
	}
}
void dis_play5()			  //mode = 5 调闹分
{
	switch(i)
	{
		case 0:display(0x01,0xbf);break;						  //显示 -
		case 1:display(0x02,0xbf);break;						  //显示 -
		case 2:display(0x04,0xbf);break;						  //显示 -
		case 3:display(0x08,seven_seg[min_n%10]|flash);break;	  //显示闹分个位    闪烁
		case 4:display(0x10,seven_seg[min_n/10]|flash);break;	  //显示闹分十位	闪烁
		case 5:display(0x20,0xbf);break;						  //显示 -
		case 6:display(0x40,seven_seg[hour_n%10]);break;		  //显示闹时个位
		case 7:display(0x80,seven_seg[hour_n/10]);break;		  //显示闹时十位
	}
}