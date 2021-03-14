#pragma once
#ifndef BulletFile
#define BulletFile

#include <vector>
#include <iostream>
#include "SDL.h"
#include "Movement.h"
#include "AABBCollision.h"
#include "EnemyObj.h"

class Bullets
{
public:
	Bullets();
	~Bullets();
	//bullet position 
	void Init(float bX, float bY, int bW, int bH);
	void Update(double deltaTime);
	//check collision on enemies 
	void CheckCollisions(const std::vector<EnemyObj*>& enemies);
	void Render(SDL_Renderer* Renderer);
	void setColour(int bR, int bG, int bB);

	Movement BulletVelocity;

	int R, G, B;

	//int counter;
	float x, y;
	int lifetime;

private:
	SDL_Rect BulletRectangle;
};

#endif