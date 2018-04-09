#define uchar unsigned char
#define uchar unsigned char
#define uint  unsigned int
sbit START=P3^4;
sbit OE=P3^6;
sbit EOC=P3^5;
uint AD;
void adc()
{
  START=1;
  START=0;
  while(EOC==0)
  {
   OE=1;
    }
    AD=P0;
	OE=0;
	}
	