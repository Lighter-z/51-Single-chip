#define uchar unsigned char											//宏定义用uchar 代替 unsigned char
#define uint unsigned int											//宏定义用uint 代替 unsigned int
sbit key1 = P1^4;													//正转				
sbit key2 = P1^5;													//反转
sbit key3 = P1^6;													//停止
uchar key1_down,key2_down,key3_down,key1_flag,key2_flag,key3_flag;	//变量定义
/***************按键函数***************/
void delay(uint x)
{
	while(x--);
}
/************按键扫描函数*************/
void key_scan(void)
{
	if(key1 == 0)													//如果按键按下
	{
		delay(100);													//消除键抖
		if(key1 == 0)key1_down = 1;	
	}
	if(key1_down == 1 && key1 == 1)									//按键按下抬起有效
	{
		key1_down = 0;
		key1_flag = 1;
		key2_flag = 0;
		key3_flag = 0;		
	}
	if(key2 == 0)													//如果按键按下
	{
		delay(100);													//消除键抖
		if(key2 == 0)key2_down = 1;									//按键按下抬起有效
	}
	if(key2_down == 1 && key2 == 1)
	{
		key2_down = 0; 
		key2_flag = 1;
		key1_flag = 0;
		key3_flag = 0;
	}
	if(key3 == 0)													//如果按键按下
	{
		delay(100);													//消除键抖
		if(key3 == 0)key3_down = 1;									//按键按下抬起有效
	}
	if(key3_down == 1 && key3 == 1)
	{
		key3_down = 0; 
		key3_flag = 1;
		key1_flag = 0;
		key2_flag = 0;
	}
}