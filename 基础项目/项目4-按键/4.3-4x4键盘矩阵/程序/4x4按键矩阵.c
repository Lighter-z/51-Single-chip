#include<reg51.h>
code P1_scan[]={0x7f,0xbf,0xdf,0xef}; //按键扫描数组

code key_temp_value[]={0xee,0xed,0xeb,0xe7,0xde,0xdd,
         0xdb,0xd7,0xbe,0xbd,0xbb,0xb7,0x7e,0x7d,0x7b,0x77};   //按键按下所对应的值

code unsigned char seven_seg[10]={0xc0,0xf9,0xa4,0xb0,0x99,	   
           0x92,0x82,0xf8,0x80,0x90};
void delay(unsigned int x)      //延时函数	
{
	while(x--);
}
unsigned char key_scan()	 //键盘扫描函数
{
	unsigned i,j;
	for(i=0;i<4;i++)		//让每个列线出现低电平（按键扫描数据）
	{
		P1=P1_scan[i];
		if(P1!=P1_scan[i])
		{
			delay(200);			 //消抖
			if(P1!=P1_scan[i])
			{
				for(j=0;j<16;j++)  //检测按键值
				{
					if(P1==key_temp_value[j])
					return(j);	  //返回按键值
				}
			}
		}
	}
	return(88);
}
void display(unsigned char i)
{
	P2=~0x01;P0 = seven_seg[i%10];		//显示按键编号个位
	delay(300);							//让个位显示一段时间
	P2=~0x02;P0 = seven_seg[i/10];		//显示按键编号十位
	delay(300);						   //让十位显示一段时间
	P0 = 0xff;						  //消隐
}
void main()
{
	unsigned char i;
	while(1)
	{
		i = key_scan();
		display(i);
	}
} 