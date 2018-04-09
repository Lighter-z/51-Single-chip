sbit key1 = P3^0;					//定义按键1接P3.0
sbit key2 = P3^1;					//定义按键2接P3.1
unsigned char i = 23;
void delay(unsigned int x)
{
	while(x--);
}
void key_scan()
{
	if(key1 == 0)					//如果按键按下
	{
		delay(300);					//延时消除按键抖动
		if(key1 == 0)				//再次判断按键是否按下
		{
			while(key1 == 0);
			i++;
			if(i > 99) i = 0;
		}
	}
	if(key2 == 0)
	{
		delay(300);
		if(key2 == 0)
		{
			while(key2 == 0);
			i--;
			if(i < 0) i = 99;
		}
	}
}