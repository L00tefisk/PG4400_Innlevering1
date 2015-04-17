#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
public:
	Timer();
	Timer(double updateRate);
	void Update();

	Uint32 time;
	Uint32 previousTime;
	Uint32 dt;
	double updateRate;
	double accumulator;
private:

};
#endif