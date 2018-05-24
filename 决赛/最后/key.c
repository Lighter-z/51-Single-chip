bit s0;
bit kai;
bit kai_1,s1;
void keyscan()
{
	if(P30 == 0)
	{
		Delay1ms();
		if(P30 == 0)
		{
			s0 = 1;
			kai = 1;
		}
	}
	if((s0 == 1) && (P30 == 1))
	{
		s0 = 0;
		kai = 0;
		if(kai == 0)
		{
			P2 = 0x80;
		P0 = 0xff;
		}
		
	}
}