#pragma once
#ifndef timer_h
#define timer_h

#include "SDL.h"

class Timer
{
private:
	uint32_t NOW = 0;
	uint32_t LAST = 0;

public:
	double deltaTime = 0;

	void tick()
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
	}

	double timeSinceLastFrame() { return deltaTime * 0.001; }
};

#endif