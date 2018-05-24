

sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST = P1^3;   // DS1302¸´Î»												

void Write_Ds1302_Byte(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302( unsigned char address,unsigned char dat )     
{
 	RST=0;
	_nop_();
 	SCK=0;
	_nop_();
 	RST=1;	
   	_nop_();  
 	Write_Ds1302_Byte(address);	
 	Write_Ds1302_Byte((dat / 10) << 4 | (dat % 10));		
 	RST=0; 
}

unsigned char Read_Ds1302 ( unsigned char address )
{
 	unsigned char i,temp=0x00;
	unsigned char low,high;
 	RST=0;
	_nop_();
 	SCK=0;
	_nop_();
 	RST=1;
	_nop_();
 	Write_Ds1302_Byte(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;
	_nop_();
 	RST=0;
	SCK=0;
	_nop_();
	SCK=1;
	_nop_();
	SDA=0;
	_nop_();
	SDA=1;
	_nop_();
	low = temp % 16;
	high = temp / 16;
	temp = high * 10 + low;
	return (temp);			
}

void Write_ds1302()
{
	unsigned char i,add = 0x80;
	Write_Ds1302(0x8e,0x00);
	for(i = 0;i < 7;i++)
	{
		Write_Ds1302(add,shijian[i]);
		add += 2;
	}
	Write_Ds1302(0x8e,0x80);
}

void Read_ds1302()
{
	unsigned char i,add = 0x81;
	Write_Ds1302(0x8e,0x00);
	for(i = 0;i < 7;i++)
	{
		shijian[i] = Read_Ds1302(add);
		add += 2;
	}
	Write_Ds1302(0x8e,0x80);
}
