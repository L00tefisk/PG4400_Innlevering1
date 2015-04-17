#include "Timer.h"
Timer::Timer(){};
Timer::Timer(double updateRate) :
updateRate(updateRate),
time(0),
previousTime(0),
dt(0),
accumulator(0.0){};


void Timer::Update()
{
	previousTime = time;
	time = SDL_GetTicks();
	dt = time - previousTime;
	accumulator += dt;
}