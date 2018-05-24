void keyscan()
{
	if(P33 == 0)
	{
		Delay1ms();
		if(P33 == 0)
		{
			while(P33 == 0);
			if((yun == 0) && (zaizhong == 2))
			{
				yun = 1;
			}
		}
	}
	
	if(P32 == 0)
	{
		Delay1ms();
		if(P32 == 0)
		{
			while(P32 == 0);
			if(yun == 1)
			{
				if(tingzhi == 0)
				{
					tingzhi = 1;
				}
				else if(tingzhi == 1)
				{
					tingzhi = 0;
				}
			}
		}
	}
	
	if(P31 == 0)
	{
		Delay1ms();
		if(P31 == 0)
		{
			while(P31 == 0);
			if(zaizhong == 1)
			{
				if(shezhi == 0)
				{
					shezhi = 1;
					shijian_yi_t = shijian_yi;
					//shijian_er_t = shijian_er;
				}
				else if(shezhi == 1)
				{
					shezhi = 2;
					//shijian_yi_t = shijian_yi;
					shijian_er_t = shijian_er;
				}
				else if(shezhi == 2)
				{
					shezhi = 0;
					IIC_Write(0x01,shijian_yi_t);
					Delay1ms();
					IIC_Write(0x02,shijian_er_t);
				}
			}
		}
	}
	
	if(P30 == 0)
	{
		Delay1ms();
		if(P30 == 0)
		{
			while(P30 == 0);
			if(zaizhong == 1)
			{
				if(shezhi == 1)
				{
					shijian_yi_t++;
					if(shijian_yi_t > 10)shijian_yi_t = 0;
				}
				else if(shezhi == 2)
				{
					shijian_er_t++;
					if(shijian_er_t > 10)shijian_er_t = 0;
				}
			}
		}
	}
}