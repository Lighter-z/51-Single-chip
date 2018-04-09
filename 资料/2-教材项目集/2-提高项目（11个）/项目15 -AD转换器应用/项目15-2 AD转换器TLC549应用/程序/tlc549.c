#define uchar unsigned char					//把 unsigned char 宏定义为 uchar
#define uint unsigned int					//把 unsigned int 宏定义为 uint
sbit sd = P3^5;								//数据线
sbit cs = P3^4;								//片选
sbit scl = P3^7;							//I/O口时钟
/********对TLC549数据转换*************/
uchar tlc549_ad(void)						//TLC549处理
{
  	uchar i,dat_temp = 0;
	scl = 0;
	cs = 0; 
  	for(i = 0;i < 8;i++)					//读取采集数据，读取的是上一次采集数据
    {	
	  	scl = 1;
		dat_temp = dat_temp << 1;   
	  	if(sd)dat_temp |= 0x01;
	  	scl = 0;   	
	} 	
  	cs = 1;
  	return(dat_temp); 
}