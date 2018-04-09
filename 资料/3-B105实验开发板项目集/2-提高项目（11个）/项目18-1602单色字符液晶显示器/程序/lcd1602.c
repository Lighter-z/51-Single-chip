#define uchar unsigned char
#define uint unsigned int
/*************延时函数***************/
void delay(uint x)
{
	while(x--);
}
sbit RS = P0^3;
sbit RW = P0^4;
sbit E  = P0^5;
uchar num[] = "0123456789";							//显示两位数字时使用
/********向LCD1602写一个命令**********/
void write_command(uchar command)
{
	RW = 0;RS = 0; send1(command);E = 1;	
	delay(100);										//等待接收，省略了读状态操作
	E = 0;
	RW = 1;
}
/*********向LCD1602写一个数据**********/
void write_data(uchar date)
{
	RW = 0;RS = 1; 	send1(date);E = 1;
	delay(100);										//等待接收
	E = 0;
	RW = 1;
}
/**********初始化LCD1602**************/
void FLCD1602_init(void)
{
	write_command(0x38);							// 两行，每行16字符，每个字符5*7点阵	
	write_command(0x0f);							// 光标显示并闪烁
	write_command(0x0C);							// 光标不显示
	write_command(0x06);							// 光标随字符右移
}
/*********对LCD1602清屏****************/
void FLCD1602_clear()
{
	write_command(0x01);	
	write_command(0x02);	
}
/***********向LCD1602写字符串**********/
void display_string(uchar *p)
{
	while(*p)										//字符非空
	{
		write_data(*p);								//写字符
		p++;										//数据指针加1
	}
}
/******向LCD1602写数字变量(两位)*******/
void display_num(uchar x)
{
	 write_data(num[x / 10]);
	 write_data(num[x % 10]);	
}
/****************定位*****************/
void gotoxy(uchar y,uchar x)
{
	if(y == 1)
	write_command(0x80 + x);						//第一行
	else if(y == 2)write_command(0x80 + 0x40 + x);	//第二行
}