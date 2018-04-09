#include <reg51.h>
#include <stdio.h>
#include <math.h>
#include "tupian.c"
uchar len;
uchar xdata RAM[64][16];
sbit    CS =P0^3;						//4号引脚
sbit    SID=P0^4;						//5号引脚
sbit    SCK=P0^5;						//6号引脚 
sbit    RES=P0^6;						//17号引脚 
void  delay(uint m)						//延时程序
{
	uint i,j;
	for(i=0;i<m;i++)
	for(j=0;j<10;j++);
}
void SendByte(uchar Dbyte)
{
     uchar i;
     for(i=0;i<8;i++)
     {
           SCK = 0;
           Dbyte=Dbyte<<1;				//左移一位
           SID = CY;					//移出的位给SID
           SCK = 1;
           SCK = 0;
     }
}
/*************************************************
写命令
*************************************************/
void TransferCom(uchar data0)  
{
  CS=1;
  SendByte(0xf8);						//11111ABC,RW(0),RS(1),0
  SendByte(0xf0&data0);					//高四位
  SendByte(0xf0&data0<<4);				//低四位(先执行<<)
  CS=0;
}

/*************************************************
写数据
*************************************************/
void TransferData(uchar data1)  
{
  CS=1;
  SendByte(0xfa);						//11111ABC,RW(0),RS(1),0
  SendByte(0xf0&data1);					//高四位
  SendByte(0xf0&data1<<4);				//低四位(先执行<<)
  CS=0;
}
/*************************************************
液晶初始化 汉字
*************************************************/
void initinal(void)						//LCD字库初始化程序
{
	delay(40);							//大于40MS的延时程序
	RES=0;								//复位
	delay(1);							//延时
	RES=1;								//复位置高
	delay(10);	
	TransferCom(0x30);					//Extended Function Set :8BIT设置,RE=0: basic instruction set, G=0 :graphic display OFF
	delay(100);							//大于100uS的延时程序
	TransferCom(0x0c);					//Display Control,D=1,显示开
	delay(100);							//大于100uS的延时程序
	TransferCom(0x01);					//Display Clear
	delay(10);							//大于10mS的延时程序
	TransferCom(0x06);					//Enry Mode Set,光标从右向左加1位移动
	delay(100);							//大于100uS的延时程序
}
//清屏函数
//********************************************************
void Display_Clear(void)
{
	TransferCom(0x01);					//写入清楚显示命令0x01
	delay(100);
}
/*************************************************
 汉字显示
*************************************************/
void lcd_mesg(uchar han,uchar lie,uchar k,uchar *chn)
{	
	uchar i;
	switch(han)
	{
		case 1:TransferCom(0x80+lie);break;
		case 2:TransferCom(0x90+lie);break;
		case 3:TransferCom(0x88+lie);break;
		case 4:TransferCom(0x98+lie);break;
		default:;
	}
	delay(100);
	len=sizeof(chn);
	for(i=0;i<k;i++)
	{
		TransferData(chn[i]);
	}
}

//**********绘图显示的清屏函数（因清屏指令在画图时不能用）
void gui_clear()
{
	uchar i,j,k;
	TransferCom(0x34);					//扩展指令集，8位数据传输
	TransferCom(0x34);					//关闭绘图
	for(i = 0; i < 2; i ++)				//分上下两屏写  
	{   
	  for(j = 0; j < 32; j ++)   
		{    
		    TransferCom(0x80 + j);		//写y坐标    
			delay(1);     
			if(i == 0)					//写x坐标    
			{      
				TransferCom(0x80);      
				delay(1);    
			}
			else						//写下半屏    
			 {      
			   TransferCom(0x88);      
			   delay(1);    
			 }     
			 for(k = 0; k < 16; k ++)	//写一整行数据    
			 {     
				 TransferData(0x00);	//写高字节     
				 TransferData(0x00);	//写低字节         
				 delay(1);
			 }   
		} 
		
   } 
   for(j=0;j<64;j++)
   {
   		for(k=0;k<16;k++)
		RAM[j][k]=0;
   }  
   TransferCom(0x36);					//打开绘图显示  
   TransferCom(0x30);					//打开基本指令集  
}
//***************有 反 白 显 示 功 能 的 打 点 函 数
void GUI_Point(unsigned char y,unsigned char x) 
{
	unsigned char x_Dyte,x_byte,xx;		//定义列地址的字节位，及在字节中的哪1位   
	unsigned char y_Dyte,y_byte;		//定义为上下两个屏(取值为0，1)，行地 址(取值为0~31)  
	unsigned char  GDRAM_h,GDRAM_l;
	TransferCom(0x36);					//扩展指令命令   /***X,Y坐标互换，即普通的X,Y坐标***/  
	xx=x/8;
	x_Dyte=x/16;						//计算在16个字节中的哪一个  
	x_byte=x%16;						//计算在该字节中的哪一位  
	y_Dyte=y/32;						//0为上半屏，1为下半屏   
	y_byte=y%32;						//计算在0~31当中的哪一行
	delay (1);
	TransferCom(0x80+y_byte);			//先写Y坐标
	TransferCom(0x80+y_Dyte*8+x_Dyte);	//先写X坐标
	delay (1);
	if(x_byte<8)
	{
		TransferData(RAM[y][xx]|0X01<<(7-x_byte));
		GDRAM_l=0X01<<(7-x_byte);
		RAM[y][xx]|=GDRAM_l;
	}
	else 
	{
		TransferData(RAM[y][xx-1]);
		TransferData(RAM[y][xx]|0X01<<(15-x_byte));
		GDRAM_h=0X01<<(15-x_byte);
		RAM[y][xx]|=GDRAM_h;
	}
	TransferCom(0x30);
}
//***************打点显示图片
void xianshi(void)
{
	uchar bb;
	uchar i,j,m;
	uint k;
	bb = aa[k];
	for(i = 0;i <= 63;i++)
	{
		for(j = 0;j <= 127;j++)
		{
			if((bb & 0x80) == 0x80)
			{
				GUI_Point(i,j);
				bb = bb << 1;
			}
			else bb = bb << 1;
			m++;
			if(m > 7)
			{
				m = 0;
				k++;
				bb = aa[k];
				k = k % 1024;
			}	
		}	
	}
}

