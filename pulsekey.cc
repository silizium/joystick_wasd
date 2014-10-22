#include "pulsekey.hh"
#include "uinput.hh"
#include <stdio.h>

void PulseKey::resetKey(int num, __u16 keycode){
	key[num]=keycode;	
	state[num]=false;
}

PulseKey::PulseKey(UInput &inp, __u16 up, __u16 down){
	resetKey(0, up);
	resetKey(1, down);
	input=inp;
}

PulseKey::~PulseKey(){}

void PulseKey::setPulse(short len){
	pulse=len/DELTA;
	//printf("Pulse: %d\n", pulse); fflush(stdout);
}

void PulseKey::tick(){
	if(--ticks<=0) {
		ticks=STEPS;
		if(pulse!=0) {
			run=pulse;
			keyDown(run>0?0:1);
		}
	}
	if(run>0){
		if(--run == 0) keyUp(0);
	}else if(run<0){
		if(++run == 0) keyUp(1);
	}
}

void PulseKey::keyDown(short num){
	if(!state[num]){
		input.key(key[num], 1);
		state[num]=true;
	}
	//printf("k%d:1 ", num); fflush(stdout);
}
void PulseKey::keyUp(short num){
	if(state[num]){
		input.key(key[num], 0);
		state[num]=false;
	}
}