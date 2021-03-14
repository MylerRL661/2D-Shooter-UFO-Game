#include "EnemyController.h"

//constructor 
EnemyController::EnemyController()
{}
//deconstructor 
EnemyController::~EnemyController()
{}

void EnemyController::Init()
{}
void EnemyController::Add(int X, int Y, SDL_Renderer *arenderer)
{
	//fast spawning
	if (c % 5000 == 0)
	{
		EnemyObj* TempBlock = new EnemyObj();
		TempBlock->setColour(0, 204, 204);
		TempBlock->Init(X, Y, 25, 25, 1, arenderer);
		this->ListofEnemies.push_back(TempBlock);
	}
}




void EnemyController::Render(SDL_Renderer * aRenderer)
{
	//render enemies 
	for (auto& element : ListofEnemies)
	{
		//if alive render
		if (element->isDead != true)
		{
			element->Render(aRenderer);
		}
	}


}
void EnemyController::Update(double deltaTime)
{
	c++;
	//add emeny to enemy list 
	for (auto& element : ListofEnemies)
	{

		if (element->isDead != true)
		{
			element->Update(deltaTime);
		}
	}
}

void EnemyController::WindowSize(int Ht, int Wh)
{
	//restarints of the window 
	for (auto& element : ListofEnemies)
	{
		element->WindowSize(Ht, Wh);
	}
}
