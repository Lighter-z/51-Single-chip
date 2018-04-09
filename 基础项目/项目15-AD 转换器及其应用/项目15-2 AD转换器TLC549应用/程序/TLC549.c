sbit sd = P3^5;							  //数据线
sbit cs = P3^4;							  //片选
sbit scl = P3^7;						  //I/O口时钟
/*对TLC549初始化*/
void tlc549_init()
{
	cs = 1;								  //初始化，时钟
	scl = 0;
	cs = 0;
}
/*对tlc549数据转换*/
uchar tlc549_ad()
{
	uchar i,dat_temp = 0;
	tlc549_init();
	for(i = 0;i < 8;i++)				  //读取上次采集的数据
	{
		scl = 1;
		dat_temp = dat_temp << 1;
		if(sd)dat_temp |= 0x01;			  //若sd = 1，dat_temp取最低位
		scl = 0;
	}
	cs = 1;
	return(dat_temp);
}