#pragma once
#ifndef PlayerFile
#define PlayerFile
#include <iostream>
#include "Movement.h"
#include <SDL_image.h>
#include "Bullets.h"
#include <SDL.h>
#include <vector>

using namespace std;

class PlayerObj
{
public:
	PlayerObj();
	~PlayerObj();
	//initialise player
	void Init(float pX, float pY, int pW, int pH, SDL_Renderer *Renderer);
	//checks enemy is being hit by player
	void Update(double deltaTime, const std::vector<EnemyObj*>& enemies);
	void Input(SDL_Event* event);
	void Render(SDL_Renderer* Renderer);
	void setColour(int cR, int cG, int cB);
	void AddBullet();
	void Shoot();
	void WindowSize(int Height, int Width);
	void CheckCollisions(const std::vector<EnemyObj*>& enemies);

	//player movement 
	Movement PlayerVelocity;

	//bullet vector
	vector<Bullets*> ListOfBullets;
	SDL_Surface* surface;
	SDL_Texture* Playertexture;
	//setting keybored values
	bool KEY_LEFT = false;
	bool KEY_RIGHT = false;
	bool KEY_UP = false;
	bool KEY_DOWN = false;
	bool SHOOT = false;

	//setting up mouse
	float x, y;
	int mouseX, mouseY;
	int height, width, R, G, B;
	int Height, Width;

	//number of bullets at once
	int Num = 8; 
	//death
	bool isDead;
	int health = 1;

private:
	SDL_Event _event;
	SDL_Rect rect;
};
#endif