#define  TYPE_LCD_DATA		1
#define  TYPE_LCD_COMMAND	0
#define  DATA   P0
sbit LCD_RST  = P2^7;
sbit LCD_RD   = P3^2;
sbit LCD_WR   = P3^3;
sbit LCD_RS   = P2^5;
sbit LCD_CS   = P2^6;
char code reserve[3]_at_ 0x3b;															//保留0x3b开始的3个字节
/**********************************************************
 延时子函数
**********************************************************/
void delay_ms(uint ms)
{
  unsigned char k;

  while (ms--)
  {
    for (k = 0; k < 228; k++)
      ;
  }
}
/**********************************************************
 写8位数据子函数
**********************************************************/
void WriteDAT(uchar value)																// color data
{
	LCD_CS =  0;
	LCD_RS 	= 1;
//	LCD_WR  = 0;
	DATA 	= value;
    LCD_WR  = 0;
	LCD_WR  = 1;
   	LCD_CS =  1;
}
/**********************************************************
 写8位命令子函数
**********************************************************/
void WriteCOM(uchar value)   															// color data
{
	LCD_CS  =  0;
	LCD_RS 	=  0;
//	LCD_WR  =  0;
	DATA 	=  value;
	LCD_WR  =  0;
	LCD_WR  =  1;
   	LCD_CS  =  1;
}
/**********************************************************
设置显示窗口子函数
**********************************************************/
void LCD_SetRamAddr(uint xStart, uint xEnd, uint yStart, uint yEnd) 
{
	WriteCOM(0x2a);		   																//行
	WriteDAT(xStart>>8);   																//XS15-XS8
	WriteDAT(xStart);	   																//XS7-XS0    (X start address)
	WriteDAT(xEnd>>8);	   																//XE15-XE8
	WriteDAT(xEnd);		   																//XE7-XE0    (X end address)
	WriteCOM(0x2b);		   																//列	row address set (RASET)
	WriteDAT(yStart>>8);   																//YS15-YS8
	WriteDAT(yStart);	 																//YS7-YS0    (Y start address)
	WriteDAT(yEnd>>8);	   																//YE15-YE8
	WriteDAT(yEnd);		   																//YE7-YE0    (Y end address)						  	
    WriteCOM(0x2c);		   																//display on	显示打开命令
}
/**********************************************************/
void LCD_init(void)
{	 																					//请看数据手册的命令部分 了解其个命令的功能
	LCD_RST=1;
	delay_ms(100);
	LCD_RST=0;
	delay_ms(100);
	LCD_RST=1;
	delay_ms(100);	
	WriteCOM(0x01);	    																//software reset软件复位
	delay_ms(100);
	WriteCOM(0x11);	    																//sleep out/power on(SLPOUT) 退出睡眠
	delay_ms(50);
	WriteCOM(0x20);																		//display inversion off 关闭取反
	delay_ms(50);
	WriteCOM(0x38);	    																//ID mode off (IDMOFF)
	delay_ms(50);
	WriteCOM(0x13);	    																//Normal display mode on (Partial mode off)	
	WriteCOM(0x3a);	    																//color mode Interface pixel format  (COLMOD)
	WriteDAT(0x05);																		//16-bit/pixel , 1-times data transfer
	WriteCOM(0xc0);																		//power control 1      (PWCTR1)
	WriteDAT(0x03);																		//default value  LCM=0 set the GVDD voltage=4.65	
	WriteCOM(0xc5);	   
	WriteDAT(0xc8);	   																	//VCOMH voltage set 4.300V	
	WriteCOM(0xc6);
	WriteDAT(0x1f);	   																	//VCOMAC voltage set 5.550V ;
	delay_ms(10);
	WriteCOM(0xfe);
	WriteDAT(0x00);
	WriteDAT(0x04);	
	WriteCOM(0x26);	   																	//gamma sel
	WriteDAT(0x04);	
	WriteCOM(0x2a);	   																	//column address set (CASET)
	WriteDAT(0x00);	  																	//XS15-XS8
	WriteDAT(0x00);	   																	//XS7-XS0    (X start address)
	WriteDAT(0x00);	   																	//XE15-XE8
	WriteDAT(0x7f);	   																	//XE7-XE0    (X end address)	
	WriteCOM(0x2b);	   																	//row address set (RASET)
	WriteDAT(0x00);	   																	//YS15-YS8
	WriteDAT(0x00);	   																	//YS7-YS0    (Y start address)
	WriteDAT(0x00);	   																	//YE15-YE8
	WriteDAT(0x9f);	   																	//YE7-YE0    (Y end address)
	WriteCOM(0x36);	   																	//memory data access control  (MADCTR)
	WriteDAT(0xc0);	
	WriteCOM(0x29);	  																	// display on
}
/**********************************************************
 清屏子函数
**********************************************************/
void  LCD_clear(uchar n)
{
   uint num;  
   LCD_SetRamAddr(0,127, 0,159);  														//设置显示的坐标
   for(num=20480;num>0;num--)          													//160*128=20480
   {
  	 WriteDAT(colors[n]>>8);   															//高8位
	 WriteDAT(colors[n]);	   															//低8位
   }
}
/**********************************************************
 图片显示子函数
**********************************************************/
void  pic_play(uint Start_X, uint End_X,uint Start_Y,uint End_Y)
{
   uint m;
   LCD_CS = 0;
   LCD_SetRamAddr(Start_X,End_X-1,Start_Y,End_Y-1);										//设置地址
   LCD_RS 	= 1; 
   for(m=0; m<(40968/2); m++)	
   {		
      WriteDAT(Image_pic[m*2+1]);														//高位在前
	  WriteDAT(Image_pic[m*2]);															//低位在后
   }
   LCD_CS = 1;
}


