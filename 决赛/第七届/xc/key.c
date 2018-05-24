void keyscan()
{
	unsigned char temp;
	P3 = 0x7f;P44 = 0;
	temp = P3;
	temp &= 0x0f;
	if(temp != 0x0f)
	{
		Delay1ms();
		temp = P3;
		temp &= 0x0f;
		if(temp != 0x0f)
		{
			temp = P3;
			switch(temp)
			{
				case 0x7e:shizhong = 1;shizhong_flag = 1;pinlv = 0;pinlv_flag = 0;dianya_an = 0;dianya_an_flag = 0;chaxun = 0;chaxun_flag = 0;break;
				case 0x7d:dianya_an = 1;dianya_an_flag = 1;shizhong = 0;pinlv = 0;pinlv_flag = 0;shizhong_flag = 0;chaxun = 0;chaxun_flag = 0;break;
				case 0x7b:pinlv = 1;pinlv_flag = 1;dianya_an = 0;shizhong = 0;shizhong_flag = 0;dianya_an_flag = 0;chaxun = 0;chaxun_flag = 0;break;
				case 0x77:
				if(shizhong_flag == 1)  //shizhong
				{
					shizhong = 0;
					shitiao++;
					if(shitiao > 3)
					{
						shitiao = 1;
					}
				}
				
				if(dianya_an_flag == 1)//dianya
				{
					dianya_an = 0;
					fazhi++;
					if(fazhi > 2)
					{
						fazhi = 1;
					}
				}
				
				if(pinlv_flag == 1)//pinlv
				{
					pinlv = 0;
					if(xinhaojiemian == 0)
					{
						xinhaojiemian = 1;
					}
					else 
					{
						xinhaojiemian = 0;
					}
				}
				
				if(chaxun_flag == 1)//chaxun
				{
					chaxun = 0;
					if(cha_flag == 0)
					{
						cha_flag = 1;
					}
					else 
					{
						cha_flag = 0;
					}
				}
				break;
			}
		}
		while(temp != 0x0f)
		{
			temp = P3;
			temp &= 0x0f;
		}
	}
	
	P44 = 1;
	P3 = 0xbf;P42 = 0;
	temp = P3;
	temp &= 0x0f;
	if(temp != 0x0f)
	{
		Delay1ms();
		temp = P3;
		if(temp != 0x0f)
		{
			switch(temp)
			{
				case 0xbe: 
					if(shitiao == 1)//shijian
					{
						shijian[2]++;
						if(shijian[2] >= 24)
						{
							shijian[2] = 23;
						}
						Write_ds1302();
					}
					else if(shitiao == 2)
					{
						shijian[1]++;
						if(shijian[1] >= 60)
						{
							shijian[1] = 59;
						}
						Write_ds1302();
					}
					else if(shitiao == 3)
					{
						shijian[0]++;
						if(shijian[0] >= 60)
						{
							shijian[0] = 59;
						}
						Write_ds1302();
					}
					
					else if(fazhi == 1)//dianya 
					{
						dianya_max = dianya_max + 500;
						if(dianya_max >= 5000)dianya_max = 5000;
						Write_at(0x00,dianya_max / 100);
					}
					else if(fazhi == 2)//dianya 
					{
						dianya_min = dianya_min + 500;
						if(dianya_min >= 5000)dianya_min = 5000;
						Write_at(0x01,dianya_min / 100);
					}
					break;
				case 0xbd:
					if(shitiao == 1)//shijian
					{
						shijian[2]--;
						if(shijian[2] <= 0)
						{
							shijian[2] = 0;
						}
						Write_ds1302();
					}
					else if(shitiao == 2)
					{
						shijian[1]--;
						if(shijian[1] <= 0)
						{
							shijian[1] = 0;
						}
						Write_ds1302();
					}
					else if(shitiao == 3)
					{
						shijian[0]--;
						if(shijian[0] <= 0)
						{
							shijian[0] = 0;
						}
						Write_ds1302();
					}
					
					
					else if(fazhi == 1)//dianya
					{
						dianya_max = dianya_max - 500;
						if(dianya_max <= 0)dianya_max = 0;	
						Write_at(0x00,dianya_max / 100);
					}				
					else if(fazhi == 2)//dianya
					{
						dianya_min = dianya_min - 500;
						if(dianya_min <= 0)dianya_min = 0;
						Write_at(0x01,dianya_min / 100);
					}
					break;
				case 0xbb: chaxun = 1;chaxun_flag = 1;dianya_an = 0;dianya_an_flag = 0;shizhong = 0;pinlv = 0;pinlv_flag = 0;shizhong_flag = 0;break;
				//case 0xb7:		break;
			}
		}
		while(temp != 0x0f)
		{
			temp = P3;
			temp &= 0x0f;
		}
	}
	P42 = 1;
}