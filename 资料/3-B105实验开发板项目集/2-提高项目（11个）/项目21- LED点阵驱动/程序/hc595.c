#define uchar unsigned char
#define uint unsigned int
sbit scp = P0^0;						//控制移位寄存器的输入
sbit sd = P0^1;							//串行数据的输入端
sbit sct = P0^2;						//控制锁存器的输出
/**********************发送一字节数据*********************/
void send(uchar x)
{
	uchar i;
	for(i = 0;i < 8;i++)				//分别向锁存器中送八位数据
	{
		scp = 0;						//每次上升沿使一位数据输出
		sd = (bit)(x & 0x80);			//高位在前
		x = x << 1;						//左移，为下一位数据输出作准备
		scp = 1;
	}
}
/**********************74HC595锁存输出********************/
void suocun(void)
{
	sct = 0;							//上升沿，使锁存器的数据输出
	sct = 1;
} 