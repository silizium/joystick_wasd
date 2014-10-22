#ifndef __PULSEKEY_HH__
#define __PULSEKEY_HH__

#include "uinput.hh"
#include <climits>
#include <linux/uinput.h>

class PulseKey{
private:
	__u16 key[2];
	bool state[2];
	const short STEPS=10;
	const short DELTA=0.9*SHRT_MAX/STEPS;
	short pulse;
	short run=0;
	short ticks=0;
	UInput input;
	
	void resetKey(int num, __u16 keycode);
	void keyDown(short num);
	void keyUp(short num);
public:
	PulseKey(UInput &inp, __u16 upkey, __u16 dnkey);
	~PulseKey();
	void tick();
	void setPulse(short len);
};

#endif