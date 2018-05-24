void keyscan()
{
	if(P30 == 0)
	{
		Delay1ms();
		if(P30 == 0)
		{
			while(P30 == 0);
			moshi++;
			if(moshi >= 2)moshi = 0;
		}
	}
	//s6
	if(P31 == 0)
	{
		Delay1ms();
		if(P31 == 0)
		{
			while(P31 == 0);
			if(moshi == 0)
			{
				tiaoshi++;
				if(tiaoshi >= 4)tiaoshi = 0;
			}
			else if(moshi == 1)
			{
				if(baojing == 0)
				{
					baojing = 1;
				}
				else if(baojing == 1)
				{
					baojing = 0;
				}
			}
		}
	}
	//s5
	if(P32 == 0)
	{
		Delay1ms();
		if(P32 == 0)
		{
			while(P32 == 0);
			if(tiaoshi == 1)
			{
				shijian[2]++;
				if(shijian[2] >= 24)
				{
					shijian[2] = 23;
				}
				Write_DS1302();
			}
			else if(tiaoshi == 2)
			{
				shijian[1]++;
				if(shijian[1] >= 60)
				{
					shijian[1] = 59;
				}
				Write_DS1302();
			}
			else if(tiaoshi == 3)
			{
				shijian[0]++;
				if(shijian[0] >= 60)
				{
					shijian[0] = 59;
				}
				Write_DS1302();
			}
			else if(baojing == 1)
			{
				baojingjuli++;
			}
		}
	}
	//s4
	if(P33 == 0)
	{
		Delay1ms();
		if(P33 == 0)
		{
			while(P33 == 0);
			if(tiaoshi == 1)
			{
				shijian[2]--;
				if(shijian[2] <= 0)
				{
					shijian[2] = 0;
				}
				Write_DS1302();
			}
			else if(tiaoshi == 2)
			{
				shijian[1]--;
				if(shijian[1] <= 0)
				{
					shijian[1] = 0;
				}
				Write_DS1302();
			}
			else if(tiaoshi == 3)
			{
				shijian[0]--;
				if(shijian[0] <= 0)
				{
					shijian[0] = 0;
				}
				Write_DS1302();
			}
			else if(baojing == 1)
			{
				baojingjuli--;
			}
		}
	}
}