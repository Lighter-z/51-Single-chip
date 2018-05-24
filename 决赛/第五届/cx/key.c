void keyscan()
{
	if(P32 == 0)
	{
		Delay1ms();
		if(P32 == 0)
		{
			while(P32 == 0);
			if(moshi == 0)
			{
				moshi = 1;
			}
			else if(moshi == 1)
			{
				moshi = 0;
			}
		}
	}
	
	if(P33 == 0)
	{
		Delay1ms();
		if(P33 == 0)
		{
			while(P33 == 0);
			s5++;
			if(s5 >= 3)s5 = 0;
		}
	}
}