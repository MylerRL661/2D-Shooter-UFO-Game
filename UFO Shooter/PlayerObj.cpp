#include "PlayerObj.h"

using namespace std;

//constructor 
PlayerObj::PlayerObj()
{}
//deconstructor
PlayerObj::~PlayerObj() 
{}

//adds new bullet
void PlayerObj::AddBullet()
{
	//create a new bullet 
	Bullets* tempBullet = new Bullets();
	tempBullet->setColour(255, 255, 255);
	//initialises bullet
	tempBullet->Init(0, 0, 5, 5);
	tempBullet->BulletVelocity.X = 0;
	tempBullet->BulletVelocity.Y = 0;
	this->ListOfBullets.push_back(tempBullet);
}

void PlayerObj::Shoot()
{
	//mouse x and y position
	SDL_GetMouseState(&mouseX, &mouseY);

	//shoot bullet in direction of mouse 
	bool NotFound = true;
	for (int i = 0; i < ListOfBullets.size() && NotFound; i++) {
		if (ListOfBullets[i]->lifetime <= 0) {
			ListOfBullets[i]->x = x + 20;
			ListOfBullets[i]->y = y + 20;


			float diffrentX = (float)mouseX - x;
			float diffrentY = (float)mouseY - y;
			float magnitude = sqrt((diffrentX*diffrentX) + (diffrentY*diffrentY));

			ListOfBullets[i]->BulletVelocity.X = (diffrentX / magnitude) * 0.5f;
			ListOfBullets[i]->BulletVelocity.Y = (diffrentY / magnitude) * 0.5f;

			//time bullet is rendered
			ListOfBullets[i]->lifetime = 10000;
			NotFound = false;
		}
	}
}

//player colour before sprite added
void PlayerObj::setColour(int cR, int cG, int cB)
{ 
	R = cR;
	G = cG;
	B = cB;
}

//keeps player in the play area
void PlayerObj::WindowSize(int HT, int WH)
{
	//Window size
	Height = HT;
	Width = WH;
}

//initialises player
void PlayerObj::Init(float pX, float pY, int pW, int pH, SDL_Renderer *Renderer)
{
	//Player start position
	x = pX;
	y = pY;
	height = pH;
	width = pW;
	rect.x = x;
	rect.y = y;
	rect.h = height;
	rect.w = width;

	//sets colour before sprite
	this->setColour(0, 255, 0);

	//shoots
	for (int i = 0; i < Num; i++)
	{
		AddBullet();
	}

	//initialises sprite to be rendered
	surface = IMG_Load(".\\Assets\\ufoRed.png");
	Playertexture = SDL_CreateTextureFromSurface(Renderer, surface);
	SDL_FreeSurface(surface);
}

//updates player
void PlayerObj::Update(double deltaTime, const std::vector<EnemyObj*>& enemies)
{
	if (isDead != true)
	{
		//speed
		float speed = 0.25f;

		//position and size
		rect.x = x;
		rect.y = y;
		rect.h = height;
		rect.w = width;

		//player movement 
		x = x + PlayerVelocity.X * deltaTime;
		y = y + PlayerVelocity.Y * deltaTime;

		for (auto& element : ListOfBullets)
		{
			element->Update(deltaTime);
			element->CheckCollisions(enemies);
		}

		//movement for all directions
		if (KEY_LEFT) PlayerVelocity.X = -speed;

		if (KEY_RIGHT) PlayerVelocity.X = speed;

		if (KEY_UP) PlayerVelocity.Y = -speed;

		if (KEY_DOWN) PlayerVelocity.Y = speed;

		//shooting
		if (SHOOT == true)
		{
			//call shoot class 
			Shoot();
			SHOOT = false;
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			if (checkCollide(x, y, rect.w, rect.h, enemies[i]->x, enemies[i]->y, enemies[i]->width, enemies[i]->height))
			{
				health -= 1;
				if (health <= 0)
				{
					isDead = true;
				}
			}
		}

		if ((KEY_RIGHT == false) && (KEY_LEFT == false))
			PlayerVelocity.X = 0;
		if ((KEY_UP == false) && (KEY_DOWN == false))
			PlayerVelocity.Y = 0;


		if (rect.x >= (Width - rect.w))
			KEY_RIGHT = false;

		if (rect.x <= 0)
			KEY_LEFT = false;

		if (rect.y >= (Height - rect.h))
			KEY_DOWN = false;

		if (rect.y <= 0)
			KEY_UP = false;
	}
}

void PlayerObj::CheckCollisions(const std::vector<EnemyObj*>& enemies)
{
	//dies
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->health > 0)
		{
			if (checkCollide(x, y, rect.w, rect.h,
				enemies[i]->x, enemies[i]->y, enemies[i]->width, enemies[i]->height))
			{
				health -= 1;
				if (health <= 0)
				{
					isDead = true;
				}
			}
		}
	}
}

//player input
void PlayerObj::Input(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN && event->key.repeat == 0)//if key is pressed 
	{
		//switch for key presses
		switch (event->key.keysym.sym)
		{
		case SDLK_a:
			KEY_LEFT = true;
			break;
		case SDLK_d:
			KEY_RIGHT = true;
			break;
		case SDLK_w:
			KEY_UP = true;
			break;
		case SDLK_s:
			KEY_DOWN = true;
			break;
		}
	}

	if (event->type == SDL_KEYUP)
	{
		//if key is not pressed
		switch (event->key.keysym.sym)
		{
		case SDLK_a:
			KEY_LEFT = false;
			break;
		case SDLK_d:
			KEY_RIGHT = false;
			break;
		case SDLK_w:
			KEY_UP = false;
			break;
		case SDLK_s:
			KEY_DOWN = false;
			break;
		}
	}
	//left mouse button is clicked
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			SHOOT = true;
		}
	}
}


void PlayerObj::Render(SDL_Renderer * Renderer)
{
	if (isDead != true)
	{
		//render elements 
		SDL_SetRenderDrawColor(Renderer, R, G, B, 255);

		//SDL_RenderDrawRect(aRenderer, &rect);
		SDL_RenderCopy(Renderer, Playertexture, NULL, &rect);

		for (auto& element : ListOfBullets)
		{
			element->Render(Renderer);
		}
	}
	else
	{
		return;
	}
}
