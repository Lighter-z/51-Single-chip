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
				case 0x7e: num = 0;key_flag = 1;break;
				case 0x7d: num = 4;key_flag = 1;break;
				case 0x7b: num = 8;key_flag = 1;break;
			//	case 0x77:    key_flag = 1;break;
			}
		}
		while(temp != 0x0f)
		{
			temp = P3;
			temp &= 0x0f;
		}
	}
	
	P44 = 1;P3 = 0xbf;P42 = 0;
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
				case 0xbe: num = 1;key_flag = 1;break;
				case 0xbd: num = 5;key_flag = 1;break;
				case 0xbb: num = 9;key_flag = 1;break;
				//case 0xb7:    key_flag = 1;break;
			}
		}
		while(temp != 0x0f)
		{
			temp = P3;
			temp &= 0x0f;
		}
	}
	
	P42 = 1;P3 = 0xdf;
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
				case 0xde: num = 2;key_flag = 1;break;
				case 0xdd: num = 6;key_flag = 1;break;
				case 0xdb: shezhi = 1;break;
				case 0xd7: queren = 1;break;
			}
		}
		while(temp != 0x0f)
		{
			temp = P3;
			temp &= 0x0f;
		}
	}
	
	P3 = 0xef;
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
				case 0xee: num = 3;key_flag = 1;break;
				case 0xed: num = 7;key_flag = 1;break;
				case 0xeb: fuwei = 1;break;
				case 0xe7: tuichu = 1;break;
			}
		}
		while(temp != 0x0f)
		{
			temp = P3;
			temp &= 0x0f;
		}
	}
}