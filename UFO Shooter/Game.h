#pragma once
#ifndef GameFILE
#define GameFILE

#include <iostream>
#include "PlayerObj.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "EnemyController.h"
#include "Bullets.h"
#include "Timer.h"
#include "SplashMenu.h"

#define LOG_IN_SECONDS

using namespace std;

class Game
{
public:
	//create player, enemy, bullet and splashscreen
	PlayerObj Player;
	EnemyController EnemySpawn;
	Bullets bullet;
	SplashScreen* splashScreen;

	//ain method
	void MainGameLoop();
	//enemy spawn method
	void CalculateEnemyPos(int* x, int* y);

	void Input();
	void Update();
	void Render();

	//create window and render
	SDL_Window* window;
	SDL_Renderer* renderer;

	Mix_Music *backgroundMusic = NULL;
	//window size
	int Width = 1000;
	int Height = 600;
	//size
	int SqareHeight = 40;
	int SqareWidth = 40;
	//spawn
	float PlayerSpawnX = 500;
	float PlayerSpawnY = 500;
	//game has started/finished
	bool gamePlaying = false;
	bool done = false;
	//60 sec timer
	Timer gameTimer;
	int lastTimeRemainingSeconds = 60;
	double timeRemaining = 60.0f;
};
#endif