code char seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
sbit din = P1^5;
sbit scl = P1^1;
sbit cs = P1^6;
void tlc5615_init(void)
{
	cs = 1;
	scl = 0;
	cs = 0;
}	 	
/*TLC5615×ª»»º¯Êý*/
void tlc5615(uint dat)
{
	uchar i;
	dat <<= 6;
	tlc5615_init();
	for(i = 0;i < 12;i++)
	{
		din = (bit)(dat & 0x8000);
		scl = 1;
		dat <<= 1;
		scl = 0;
	} 
	cs = 1;
	scl = 0;
}															