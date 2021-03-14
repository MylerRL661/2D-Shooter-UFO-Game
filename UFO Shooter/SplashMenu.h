#pragma once
#ifndef splash_h
#define splash_h

#include <vector>
#include "OnScreenText.h"

class SplashScreen
{
private:
	std::vector<ScreenText*> elements;

public:
	SplashScreen(SDL_Window* window);
	~SplashScreen();

	void Input(SDL_Event* event, bool* gamePlaying);
	void Update();
	void Render();
};

#endif