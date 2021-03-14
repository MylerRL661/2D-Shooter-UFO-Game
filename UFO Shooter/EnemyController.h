#pragma once
#ifndef EnemyControlFILE
#define EnemyControlFILE

#include <vector>
#include <iostream>
#include <SDL.h>
#include "EnemyObj.h"

using namespace std;

class EnemyController
{
public:
	EnemyController();
	~EnemyController();
	
	void Init();
	void Add(int X, int Y, SDL_Renderer *renderer);
	void Render(SDL_Renderer* Renderer);
	void Update(double deltaTime);
	void WindowSize(int Ht, int Wh);

	vector<EnemyObj*>ListofEnemies;
	//max number of enemies
	int MaxNum; 
	//number of enemies
	int NumEmenies;
	//enemy counter
	int c;
	//bool to check if they are dead
	bool isDead = false;
};

#endif 