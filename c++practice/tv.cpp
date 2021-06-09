#include <iostream>
#include "tv.h"
#pragma once


bool tv::volup()
{
	if (volume < MaxVal)
	{
		volume++;
		return true;
	}
	else
		return false;
}
bool tv::voldown()
		{
			if (volume > MaxVal)
			{
				volume--;
				return true;
			}
			else
				return false;
}

void tv::chanup()
{
	if (channel < maxchannel)
		channel++;
	else
		channel = 1;
}
void tv::chandown()
{
	if (channel >1)
		channel--;
	else
		channel = maxchannel;
}
void tv::settings() const
{
	using std::cout;
	using std::endl;
	cout << "TV = " << (state == Off ? "OFF" : "ON") << endl;
	if (state == On)
	{
		cout << "���� = " << volume << endl;
		cout << "ä�� = " << channel << endl;
		cout << "��� = " << (mode == Antenna ? "������ ���" : "���̺� ���") << endl;
		cout << "�Է� = " << (input == TV ? "TV" : "DVD") << endl;
	}
}

