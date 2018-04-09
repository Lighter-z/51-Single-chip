#include<reg51.h>
sbit key1 = P1^4;																//模式键
sbit key2 = P1^5;																//增加键
sbit key3 = P1^6;																//减少键
sbit key4 = P1^7;																//退出设定，取消闹铃
bit key1_s,key2_s,key3_s,key4_s;												//按键按下状态
unsigned char hour = 12,min = 30,sec =30;										//正在走的时间变量
char hour_t,min_t,sec_t;														//调整的中间时间变量
unsigned char min_r,hour_r;														//定闹的时间变量
unsigned char key1_flag;														//调整控制变量，控制调整对象、控制显示对象
void delay(unsigned int x)														//延时函数
{											   	
	while(x--);
}											 	
void key(void)																	//按键函数
{
	if(key1 == 0)																//按键key1处理
	{
		delay(300);
		if(key1 == 0);
		key1_s = 1;
	}
	if(key1 == 1 && key1_s == 1)
	{
		key1_s = 0;
		key1_flag++;
		if(key1_flag >= 6)key1_flag = 1;
		hour_t = hour;															//把正在走的时间给调整值
		min_t = min;
		sec_t = sec;	
	}
	if(key2 == 0)																//按键key2处理
	{
		delay(300);
		if(key2 == 0);
		key2_s = 1;
	}
	if(key2 == 1 && key2_s == 1)
	{
		key2_s = 0;
		if(key1_flag == 1)hour_t++;if(hour_t >= 24)hour_t = 0;hour = hour_t;	//对小时进行调节，把调整后的时间赋值给走的时间
		if(key1_flag == 2)min_t++;if(min_t >= 60)min_t = 0;min = min_t;			//对分钟进行调节，把调整后的时间赋值给走的时间
		if(key1_flag == 3)sec_t++;if(sec_t >= 60)sec_t = 0;sec = sec_t;			//对小时进行调节，把调整后的时间赋值给走的时间
		if(key1_flag == 4)hour_r++;if(hour_r >= 24)hour = 0;					//对小时进行调节，把调整后的时间赋值给走的时间
		if(key1_flag == 5)min_r++;if(min_r >= 24)min_r = 0;						//对小时进行调节，把调整后的时间赋值给走的时间
	}
	if(key3 == 0)																//按键key3处理
	{
		delay(300);
		if(key3 == 0);
		key3_s = 1;
	}
	if(key3 == 1 && key3_s == 1)
	{
		key3_s = 0;
		if(key1_flag == 1)hour_t--;if(hour_t <= 0)hour_t = 23;hour = hour_t;
		if(key1_flag == 2)min_t--;if(min_t <= 0)min_t = 59;min = min_t;
		if(key1_flag == 3)sec_t--;if(sec_t <= 0)sec_t = 59;sec = sec_t;
		if(key1_flag == 4)hour_r--;if(hour_r <= 0)hour = 23;
		if(key1_flag == 5)min_r--;if(min_r <= 0)min_r = 59;		
	}
 	if(key4 == 0)																//按键key4处理
	{
		delay(300);
		if(key4 == 0);
		key4_s = 1;
	}
	if(key4 == 1 && key4_s == 1)																				
	{
		key1_flag = 0;
		key4_s = 0;
	}
}
