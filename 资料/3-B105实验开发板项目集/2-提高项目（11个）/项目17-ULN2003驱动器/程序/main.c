//ULN2003驱动器教材和B105型实验开发板通用
//key1_falg控制电机正转  key2_flag控制电机反转 key3_flag控制电机停止
//设计：单片机创新工作室--王曙光设计，2015年12月15日
#include<reg51.h>
#include <key.c>
#include <moto.c>
void main(void)
{ 
   	while(1)
    {  
      	key_scan();
		if(key1_flag == 1)
			motor_ffw();			//电机正转
		if(key2_flag == 1)
			motor_rev();			//电机反转
      	if(key3_flag == 1) 
			P2 = 0x0f;				//电机停止
	}
}