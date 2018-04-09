//proteus仿真论坛：proteus.5d6d.com
#include <reg51.h>
#include <intrins.h>
#include <ADC0808.c>
sbit DI=P2^2; // 数据\指令 选择
sbit RW=P2^1; // 读\写 选择
sbit E=P2^0; // 读\写使能
sbit CS1=P2^4; // 片选1
sbit CS2=P2^3; // 片选2
sbit busy=P1^7;
sbit jia=P3^7;
sbit jian=P3^3;
sbit jia1=P3^0;
sbit jian1=P3^1;
unsigned int i;
unsigned char ye,lei,shu;
unsigned char a[91];
char code t[]={	
                
																				 
			    0x00,0x00,0x08,0x00,0x04,0x00,0x02,0x00,0x01,0x80,0x40,0x60,0x80,0x00,0x7F,0xFF, //小
                0x00,0x00,0x00,0x20,0x00,0x40,0x00,0x80,0x01,0x00,0x06,0x00,0x00,0x00,0x00,0x00,

				0x00,0x80,0x00,0x80,0x00,0x82,0x00,0x82,0x00,0x82,0x40,0x82,0x80,0x82,0x7F,0xE2, //子
                0x00,0xA2,0x00,0x92,0x00,0x8A,0x00,0x86,0x00,0x80,0x00,0xC0,0x00,0x80,0x00,0x00,
																								 
				0x00,0x40,0x00,0x60,0x3F,0x5E,0x01,0x48,0x01,0x48,0xFF,0xFF,0x11,0x48,0x21,0x4C, //制
                0x1F,0x68,0x00,0x40,0x07,0xF8,0x40,0x00,0x80,0x00,0x7F,0xFF,0x00,0x00,0x00,0x00,
				
				0x00,0x80,0x00,0x40,0x00,0x20,0xFF,0xF8,0x00,0x87,0x00,0x40,0x00,0x30,0x00,0x0F, //作
                0xFF,0xF8,0x08,0x88,0x08,0x88,0x08,0xC8,0x0C,0x88,0x08,0x0C,0x00,0x08,0x00,0x00, 
				};


             		  
void checkstate()
{
    DI=0;
	RW=1;
	do
	{
	  E=1; 
	  E=0;
					//仅当第7位为0时才可操作(判别busy信号)
	}while(busy==1);
}
   void writecommand(unsigned char command) 	//写命令
{
	checkstate();
	DI=0;
	RW=0;
	P1=command;
	E=1;
	E=0;
	}
 void writedate(unsigned char date)		//写数据
{
   checkstate();
   DI=1; 
   RW=0;
   P1=date;
   E=1; 
   E=0; 
}

 void pianxuan(unsigned int i)
 {
  if(i==1) 
  CS1=0,CS2=1;
  if(i==2)
  CS1=1,CS2=0;
  if(i==3)
  CS1=0,CS2=0;
  }
  void shuju()
 {
  pianxuan(i);
  writecommand(ye);
  writecommand(lei);
  writedate(shu);
  }
  void cleanscreen()						 //清屏
{
	unsigned char page,i;
	pianxuan(3);
	 for(page=0xb8;page<=0xbf;page++)
	{   
		writecommand(page);
		writecommand(0x40);
		for(i=0;i<64;i++)
		writedate(0x00);
		
}
	pianxuan(1);
    lei=0x40;
	for(ye=0xb8;ye<0xbf;ye++)
	{
	 shu=0xff;
	 shuju();
	 }
	 ye=0xb8;
	 for(lei=0x40;lei<=0x7f;lei++)
	 {
	  shu=0x80;
	  shuju();
	  }
	 ye=0xbf;
	 for(lei=0x40;lei<=0x7f;lei++)
	 {
	  shu=0x01;
	  shuju();
	  }
    pianxuan(2);
    ye=0xb8;
	for(lei=0x40;lei<=0x5b;lei++)
	 {
	  shu=0x80;
	  shuju();
	  }
	  ye=0xbf;
	 for(lei=0x40;lei<=0x5b;lei++)
	 {
	  shu=0x01;
	  shuju();
	  }
	 lei=0x5b;
	  for(ye=0xb9;ye<=0xbe;ye++)
	{
	 shu=0xff;
	 shuju();
	 }
	 
}
void init(void)   //开显示，起始行0行
{	
    writecommand(0xc0);
	writecommand(0x3f);
}
void delay_50us(uint t)
{
 uchar j;  
 for(;t>0;t--)   
  for(j=19;j>0;j--);
}
 
void qing()
 {
  uchar i;
  for(i=0xb9;i<=0xbe;i++)
  {
    ye=i;
	shu=0x00;
	shuju();
	}
  }
 void main()
 {
 
	
    uint r,j,g=0,q,dianya=1,k,p;
    uchar m,l;
	//pianxuan(3);
    cleanscreen();
    init();
	pianxuan(2);
	l=0xb8;
	for(k=0;k<4;k++,l=l+0x02)
	{
	ye=l;
	lei=0x70;
	for(r=0;r<16;r++)
   {
    shu=t[2*r+1+32*k];
	shuju();
	lei++;
	}
	ye=l+0x01;
	lei=0x70;
	for(r=0;r<16;r++)
   {
    shu=t[2*r+32*k];
	shuju();
	lei++;
	}
	}
  while(1)
  {
uchar d1,d2,d3,d4,d5,d6;
while(jia==0)
{
 while(jia==0);
 g=g+1;
 }
 while(jian==0)
{
 while(jian==0);
 if(g!=0) g=g-1;
 }
 while(jia1==0)
{
 while(jia1==0);
 dianya=dianya+1;
 }
 while(jian1==0)
{
 while(jian1==0);
 if(dianya!=1) dianya=dianya-1;
 }
 for(j=0;j<90;j++) //AD采样最大值
 {
  adc();
  a[j]=AD;
  if(a[j]>a[91])
  {
   a[91]=a[j];
   }
  delay_50us(g);
  }
  
 while(AD!=a[91])
 {
  adc();
  }
for(j=0;j<90;j++) //AD采样
 {
  adc();
  a[j]=AD; 
  delay_50us(g);
  }
    lei=0x41;
    for(r=0,j=0;r<90;r++,j++)
	{
   	if(j<63) i=1;
	if(j==63) lei=0x40;
	if(j>=63)i=2;
	qing();
	if(a[j>=127])//正电压
	{                             
    AD=(a[j]-127)*0.196/dianya;  //计算在12864的电压值
    if(AD<=7)       ye=0xbb,shu=(0x80>>AD);
	else if(AD<=15) ye=0xba,shu=(0x80>>(AD-8));
    else if(AD<=23) ye=0xb9,shu=(0x80>>(AD-16));
    else if(AD<=31) ye=0xb9,shu=(0x80>>(AD-24));
	}
	if(a[j]<127)//负电压
	{
	AD=(127-a[j])*0.196/dianya;
    if(AD<=7)       ye=0xbc,shu=(0x01<<(AD));
    else if(AD<=15) ye=0xbd,shu=(0x01<<(AD-8));
    else if(AD<=23) ye=0xbe,shu=(0x01<<(AD-16));
	else if(AD<=31) ye=0xbe,shu=(0x01<<(AD-24));
	}
   if(r==0)
	{
	d1=shu;
	d2=ye;
	}
	if(r!=0)
	{
	 d3=shu;
	 d4=ye;
	 if(ye==d2)
	 {
	  if(shu>d1)
	 {
	 d5=shu;
	 d5=d5>>1;
	 while(d5!=d1)
	 {d5=d5>>1;
	 shu=shu|(shu>>1);}
	 }
	 if(shu<d1)
	 {
	 d5=shu;
	 d5=d5<<1;
	 while(d5!=d1)
	 {d5=d5<<1;shu=shu|(shu<<1);} 
	 }
	}
 
    if(ye<d2)
	 {
	     for(q=0;q<7;q++) 
	     {
		  shu=shu|(shu<<1);
		  } 
		  shuju();
	 	  ye++;
		  while(ye<d2) {shu=0xff,shuju(),ye++;}
		  if(ye==d2){
		              shu=0x01;
					  if(shu<d1)
	                {
	                 d5=shu;
	                 d5=d5<<1;
	                 while(d5!=d1)
	                 {d5=d5<<1;shu=shu|(shu<<1);} 
	                  }
					  }
       }
	  if(ye>d2)
	 {
	     for(q=0;q<7;q++) 
	        {
		      shu=shu|(shu>>1);
		     }
		  shuju();
	 	  ye--;
		  while(ye>d2) {shu=0xff,shuju(),ye--;}
		  if(ye==d2){
		              shu=0x80;
					  if(shu>d1)
	                   {
	                 d5=shu;
	                 d5=d5>>1;
	                 while(d5!=d1)
	                 {d5=d5>>1;shu=shu|(shu>>1);} 
	                    }
					 } 
      }
	  }
	if(r!=0)
	{
	 d1=d3;
	 d2=d4;
	 }
	shuju();
    if(lei!=0x7f) lei++;
	}
	 }
	 }
	
	  
   
	