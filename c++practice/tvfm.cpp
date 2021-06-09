#include <iostream>
#include "tvfm.h"
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
	if (channel > 1)
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
		cout << "볼륨 = " << volume << endl;
		cout << "채널 = " << channel << endl;
		cout << "모드 = " << (mode == Antenna ? "지상파 방송" : "케이블 방송") << endl;
		cout << "입력 = " << (input == TV ? "TV" : "DVD") << endl;
	}
}
inline void Remote::set_chan(tv & t, int c) { t.channel = c; }
void Remote::show_remotemode()
{
	using std::cout;
	using std::endl;
	cout << "리모컨의 모드는 " << (remotemode == Normal ? "일반" : "대화") << "모드입니다." << endl;
}
