sbit din = P1^5;							//特殊位定义 数据输入端口
sbit scl = P1^1;							//特殊位定义 脉冲端口
sbit cs = P1^6;								//特殊位定义 芯片片选端口
#define uchar unsigned char					//宏定义 即用uchar 代替unsigned char 
#define uint unsigned int					//宏定义 即用uint 代替unsigned int
/***************TLC5615初始化函数*********************/
void tlc5615_init(void)
{
	cs = 1;
	scl = 0;
	cs = 0;
}

/* ************TLC5615转换函数***********************/
void tlc5615(uint dat)						//由于TLC5615是十位转换，定义一个16位的变量
{
	uchar i;
	dat <<= 6;								//两个字节有十六位，去掉高六位剩下十位有效位
	tlc5615_init();							//初始化
	for(i = 0;i < 12;i ++)	
	{
		din = (bit)(dat & 0x8000);
		scl = 1;							//前面一句亦可用DA = CY来代替，但后面的顺序要调换才行
		dat <<= 1;
		scl = 0;
	}
	cs = 1;
	scl = 0;       
}