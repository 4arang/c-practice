#pragma once
class tv
{
public :
	friend class Remote;
	enum { Off, On };
	enum {MinVal, MaxVal = 20};
	enum {Antenna, Cable};
	enum {TV, DVD};

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
private:
	int mode;
public:
	Remote(int m = tv::TV) : mode(m) {}
	bool volup(tv & t) { return t.volup(); }
	bool voldown(tv & t) { return t.voldown(); }
	void onoff(tv & t) { t.onoff(); }
	void chanup(tv & t) { t.chanup(); }
	void chandown(tv & t) { t.chandown(); }
	void set_chan(tv & t, int c) { t.channel = c; }
	void set_mode(tv & t) { t.set_mode(); }
	void set_input(tv&t) { t.set_input(); }
};
