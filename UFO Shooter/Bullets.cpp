#include "Bullets.h"

using namespace std;
//constructor
Bullets::Bullets() 
{}
//deconstrutor
Bullets::~Bullets()
{}

//initialise bullet
void Bullets::Init(float bX, float bY, int bW, int bH)
{
	x = bX;
	y = bY;
	BulletRectangle.x = x;
	BulletRectangle.y = y;
	BulletVelocity.X = 0.0f;
	BulletVelocity.Y = 0.0f;
	BulletRectangle.w = bW;
	BulletRectangle.h = bH;

	lifetime = 0;
}

//updates bullet
void Bullets::Update(double deltaTime)
{
	x += BulletVelocity.X * deltaTime;
	y += BulletVelocity.Y * deltaTime;
	BulletRectangle.x = x;
	BulletRectangle.y = y;

	//destroys bullet on collision
	if (lifetime > 0)
	{
		lifetime--;
	}
}

void Bullets::CheckCollisions(const std::vector<EnemyObj*>& enemies)
{
	if (lifetime > 0)
	{
		for (int i = 0; i < enemies.size(); i++) 
		{
			//if enemies alive
			if (enemies[i]->health > 0) 
			{
				if (checkCollide(x, y, BulletRectangle.w, BulletRectangle.h,
					enemies[i]->x, enemies[i]->y, enemies[i]->width, enemies[i]->height))
				{
					SDL_Log("Bullet has collided with enemy %i at position x=%f, y=%f!", i, enemies[i]->x, enemies[i]->y);
					// take health
					enemies[i]->health -= 1;
					//if no health 
					if (enemies[i]->health <= 0)
					{
						//enemy dies
						enemies[i]->isDead = true;
					}
					//destroy bullet
					lifetime = 0; 
				}
			}
		}

	}
}

//renders bullet
void Bullets::Render(SDL_Renderer* Renderer)
{
	if (lifetime > 0)
	{
		SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
		SDL_RenderDrawRect(Renderer, &BulletRectangle);
	}
}

//sets bullet colours 
void Bullets::setColour(int bR, int bG, int bB) 
{
	R = 255;
	G = 51;
	B = 51;
}