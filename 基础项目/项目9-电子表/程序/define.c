#define uchar unsigned char;
#define uint unsigned int;
sbit key_set = P2^0;
sbit key_up = P2^1;
sbit key_down = P2^2;
sbit P3_0 = P3^0;
sbit P3_2 = P3^2; //·äÃùÆ÷
sbit P2_4 = P2^4;
uchar sec = 45,min = 12,hour;
uchar sec_t,min_t,hour_t;
uchar min_n = 13,hour_n;
uchar cp,cp1;
uchar flash,mode,i;
code uchar seven_seg[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,
			0x82,0xf8,0x80,0x90};

