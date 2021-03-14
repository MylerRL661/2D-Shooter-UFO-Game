#include "EnemyObj.h"

using namespace std;

//constructor 
EnemyObj::EnemyObj()
{}
//deconstructor 
EnemyObj::~EnemyObj()
{}

//set colours - changed to sprite
void EnemyObj::setColour(int eR, int eG, int eB)
{
	R = eR;
	G = eG;
	B = eB;

}

//enemy initialisation
void EnemyObj::Init(float eX, float eY, int eW, int eH, int HTLH, SDL_Renderer *aRenderer)
{
	health = HTLH;
	//positions
	x = eX;
	y = eY; 
	height = eH;
	width = eW;
	//enemy sizes
	EnemyRect.x = x;
	EnemyRect.y = y;
	EnemyRect.h = height;
	EnemyRect.w = width;
	//force of movement 
	EnemyVel.X = 0.2f;
	EnemyVel.Y = -0.2f;

	surface = IMG_Load(".\\Assets\\enemyBlack1.png");
	enemyTexture = SDL_CreateTextureFromSurface(aRenderer, surface);
	SDL_FreeSurface(surface);
}

void EnemyObj::Update(double deltaTime)
{
	//stops enemy leaving play area
	if (EnemyRect.x >= (Width - EnemyRect.w))
		EnemyVel.X = -0.25f;

	if (EnemyRect.x <= 0)
		EnemyVel.X = 0.25f;

	if (EnemyRect.y >= (Height - EnemyRect.h))
		EnemyVel.Y = -0.1f;

	if (EnemyRect.y <= 0)
		EnemyVel.Y = 0.1f;


	x += EnemyVel.X * deltaTime;
	y += EnemyVel.Y * deltaTime;

	EnemyRect.x = (int)x;
	EnemyRect.y = (int)y;
}

void EnemyObj::Render(SDL_Renderer* aRenderer)
{
	//render enemy 
	SDL_SetRenderDrawColor(aRenderer, R, G, B, 255);
	//SDL_RenderDrawRect(aRenderer, &EnemyRect);
	SDL_RenderCopy(aRenderer, enemyTexture, NULL, &EnemyRect);
}

void EnemyObj::WindowSize(int Ht, int Wh)
{
	//window size 
	Height = Ht;
	Width = Wh;
}
