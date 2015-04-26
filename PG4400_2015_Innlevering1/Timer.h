#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
public:
	Timer();
	Timer(double updateRate);
	void Update();

	Uint32 updateRate;
	Uint32 accumulator;
private:
	Uint32 time;
	Uint32 previousTime;
	Uint32 dt;
	
};
#endif