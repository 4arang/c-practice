#pragma once

class Remote;
class tv
{

	friend class Remote;

public:
	void remotemodecontrol(Remote & r);
	enum { Off, On };
	enum { MinVal, MaxVal = 20 };
	enum { Antenna, Cable };
	enum { TV, DVD };

	tv(int s = Off, int mc = 125) : state(s), volume(5),
		maxchannel(mc), channel(2), mode(Cable), input(TV) {}
	void onoff() { state = (state == On) ? Off : On; }
	bool ison() const { return state == On; }
	bool volup();
	bool voldown();
	void chanup();
	void chandown();
	void set_mode() { mode = (mode == Antenna) ? Cable : Antenna; }
	void set_input() { input = (input == TV) ? DVD : TV; }
	void settings() const;


private:
	int state;
	int volume;
	int maxchannel;
	int channel;
	int mode;
	int input;
};

class Remote
{
	friend class tv;
private:
	int mode;
	int remotemode; //
public:
	enum {Normal, Conversation};
	Remote(int m = tv::TV, int m2 = Normal) : mode(m), remotemode(m2) {}
	bool volup(tv & t) { return t.volup(); }
	bool voldown(tv & t) { return t.voldown(); }
	void onoff(tv & t) { t.onoff(); }
	void chanup(tv & t) { t.chanup(); }
	void chandown(tv & t) { t.chandown(); }
	void set_chan(tv & t, int c);
	void set_mode(tv & t) { t.set_mode(); }
	void set_inpuT(tv&t) { t.set_input(); }
	void show_remotemode();
};
inline void tv::remotemodecontrol(Remote & r)
{
	if (state == On)
	{
		r.remotemode = (r.remotemode == Remote::Normal) ? Remote::Conversation : Remote::Normal;
	}
}


/*
class tv;

class Remote
{
public:
	enum State{ Off, On };
	enum { MinVal, MaxVal = 20 };
	enum { Antenna, Cable };
	enum { TV, VCR };
private:
	int mode;
public:
	Remote(int m = tv::TV) : mode(m) {}
	bool volup(tv & t);
	bool voldown(tv & t);
	void onoff(tv & t);
	void chanup(tv & t);
	void chandown(tv & t);
	void set_chan(tv & t, int c);
	void set_mode(tv & t);
	void set_input(tv&t);

};
class tv
{
public:
	friend void Remote::set_chan(tv & t, int c);
	enum State{ Off, On };
	enum { MinVal, MaxVal = 20 };
	enum { Antenna, Cable };
	enum { TV, DVD };

	tv(int s = Off, int mc = 125) : state(s), volume(5),
		maxchannel(mc), channel(2), mode(Cable), input(TV) {}
	void onoff() { state = (state == On) ? Off : On; }
	bool ison() const { return state == On; }
	bool volup();
	bool voldown();
	void chanup();
	void chandown();
	void set_mode() { mode = (mode == Antenna) ? Cable : Antenna; }
	void set_input() { input = (input == TV) ? DVD : TV; }
	void settings() const;

private:
	int state;
	int volume;
	int maxchannel;
	int channel;
	int mode;
	int input;
};



inline bool Remote:: volup(tv & t) { return t.volup(); }
inline bool Remote::voldown(tv & t) { return t.voldown(); }
inline void Remote:: onoff(tv & t) { t.onoff(); }
inline void Remote::chanup(tv & t) { t.chanup(); }
inline void Remote::chandown(tv & t) { t.chandown(); }
inline void Remote::set_chan(tv & t, int c) { t.channel = c; }
inline void Remote::set_mode(tv & t) { t.set_mode(); }
inline void Remote::set_input(tv&t) { t.set_input(); }
*/