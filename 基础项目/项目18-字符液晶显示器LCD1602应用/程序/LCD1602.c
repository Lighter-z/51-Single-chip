uchar num[] = "0123456789";	   
sbit RS = P2^2;
sbit RW = P2^1;
sbit E = P2^0;	
void delay(uint x)
{
	while(x--);	
} 

void write_command(uchar command)
{
	RW = 0;
	RS = 0;
	P0 = command;
	E = 1;
	delay(100);
	E = 0;
	RW = 1;
} 
void write_data(uchar date)
{
	RW = 0;
	RS = 1;
	P0 = date;
	E = 1;
	delay(100);
	E = 0;
	RW = 1;
} 
void FLCD1602_init(void)
{
	write_command(0x38);
	write_command(0x0f);
	//write_command(0x0c);
	write_command(0x06);
}  
void FLCD1602_clear()
{
	write_command(0x01);
	write_command(0x02);
}
void display_string(uchar *p)
{
	while(*p)
	{
		write_data(*p);
		p++;
	}
}
void display_num(uchar x)
{
	write_data(num[x / 10]);
	write_data(num[x % 10]);
}
void gotoxy(uchar y,uchar x)
{
	if(y == 1)
	write_command(0x40 + x);
	else if(y == 2)
	write_command(0x80 + 0x40 + x);
}				

