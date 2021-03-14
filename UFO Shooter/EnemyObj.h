#pragma once
#ifndef EnemyFILE
#define EnemyFILE
#include <iostream>
#include <SDL.h>
#include "Movement.h"
#include <SDL_image.h>

class EnemyObj
{
public:
	EnemyObj();
	~EnemyObj();
	void setColour(int eR, int eG, int eB);
	//position and sprite render
	void Init(float eX, float eY, int eW, int eH, int HTLH, SDL_Renderer *aRenderer);
	void Update(double deltaTime);
	void Render(SDL_Renderer* aRenderer);
	void WindowSize(int Ht, int Wh);
	Movement EnemyVel;

	//declearing values 
	int height, width, R, G, B;
	int Height, Width;
	float x, y;
	//enemy health and isDead bool - similar to controller
	int health;
	bool isDead = false;
	SDL_Surface* surface;
	SDL_Texture* enemyTexture;



private:
	SDL_Rect EnemyRect;
};
#endif