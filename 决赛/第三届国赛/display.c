
void mi()
{
	yi = 10;er = 10;
	if(key_flag == 1)
	{
		mima[i++] = num;
		key_flag = 0;
	}
	if(queren == 1)
	{
		i = 0;
		queren = 0;
		for(j = 0;j < 6;j++)
		{
			if(anwser[j] != mima[j])
			{
				wrong = 1;
			}
		}
		if(wrong == 1)
		{
			k = k + 1;
			for(j = 0;j < 6;j++)
			{
				mima[j] = 11;
			}
			wrong = 0;
			if(k >= 3)
			{
				fengmingqi = 1;
				P2 = 0xa0;
				P0 = 0x40;
			}
		}
		else
		{
			P2 = 0xa0;
			P0 = 0x10;
			jidianqi = 1;	
			for(j = 0;j < 6;j++)
			{
				mima[j] = 11;
			}
			k = 0;
		}
	}
}

void xiugai()
{
	yi = 11;er = 10;
	if(key_flag == 1)
	{
		chongzhi[i++] = num;
		key_flag = 0;
	}
	if(queren == 1)
	{
		i = 0;
		queren = 0;
		for(j = 0;j < 6;j++)
		{
			if(anwser[j] != chongzhi[j])
			{
				wrong = 1;
			}
		}
		if(wrong == 0)
		{
			k = 0;
			for(j = 0;j < 6;j++)
			{
				chongzhi[j] = 11;
			}
			chongzhi_flag = 1;
		}
		else if(wrong == 1)
		{
			k = k + 1;
			for(j = 0;j < 6;j++)
			{
				chongzhi[j] = 11;
			}
			wrong = 0;
			if(k >= 3)
			{
				fengmingqi = 1;
				P2 = 0xa0;
				P0 = 0x40;
			}
		}
	}
}

void xinmima()
{
	yi = 10;
	er = 11;
	if(key_flag == 1)
	{
		newmima[i++] = num;
		key_flag = 0;
	}
	if(queren == 1)
	{
		i = 0;
		queren = 0;
		for(j = 0;j < 6;j++)
		{
			anwser[j] = newmima[j];
			newmima[j] = 11;
		}
		add = 0x01;
		for(z = 0;z < 6;z++)
		{
			Write_AT24c04(add,anwser[z]);
			Delay1ms();
			add = add + 1;
		}
		shezhi = 0;
		chongzhi_flag = 0;
	}
}

void chushihua()
{
	if(fuwei == 1)
	{
		k = 0;
		i = 0;
		for(j = 0;j < 6;j++)
		{
			anwser[j] = moren[j];
			newmima[j] = 11;
			chongzhi[j] = 11;
		}
		shezhi = 0;
		fuwei = 0;
		chongzhi_flag = 0;
	}
	else if(tuichu == 1)
	{
		k = 0;
		i = 0;
		for(j = 0;j < 6;j++)
		{
			newmima[j] = 11;
			chongzhi[j] = 11;
		}
		shezhi = 0;
		tuichu = 0;
		chongzhi_flag = 0;
	}
}

void display()
{
	if(shezhi == 1)
	{
		if(chongzhi_flag == 0)
		{
			san = chongzhi[0];si = chongzhi[1];wu = chongzhi[2];
			liu = chongzhi[3];qi = chongzhi[4];ba = chongzhi[5];
			xiugai();
			chushihua();
			xianshi();
		}
		else if(chongzhi_flag == 1)
		{
			san = newmima[0];si = newmima[1];wu = newmima[2];
			liu = newmima[3];qi = newmima[4];ba = newmima[5];
			xinmima();
			chushihua();
			xianshi();
		}
		
	}
	else
	{
		ceju();
		if(juli <= 30)
		{
			if((shijian[2] >= 7) && (shijian[2] <= 22))
			{
				yi = shijian[2] / 10;
				er = shijian[2] % 10;
				san = 10;
				si = shijian[1] / 10;
				wu = shijian[1] % 10;
				liu = 10;
				qi = shijian[0] / 10;
				ba = shijian[0] % 10;
				xianshi();
				P2 = 0xa0;
				P0 = 0x10;
				jidianqi = 1;	
			}
			else
			{
				mi();
				san = mima[0];si = mima[1];wu = mima[2];
				liu = mima[3];qi = mima[4];ba = mima[5];
				xianshi();
			}
		}
		else
		{
			yi = shijian[2] / 10;
			er = shijian[2] % 10;
			san = 10;
			si = shijian[1] / 10;
			wu = shijian[1] % 10;
			liu = 10;
			qi = shijian[0] / 10;
			ba = shijian[0] % 10;
			xianshi();
		}
	}	
}