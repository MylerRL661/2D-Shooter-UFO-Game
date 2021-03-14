#include "SplashMenu.h"

//splash screen settings
SplashScreen::SplashScreen(SDL_Window* window)
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	elements.push_back(new ScreenText(window, "./Assets/Staatliches-Regular.ttf", 32));
	elements[elements.size() - 1]->setText("UFO Invasion!", w / 2, 100, true, 40, 255, 1, 1);

	elements.push_back(new ScreenText(window, "./Assets/Staatliches-Regular.ttf", 24));
	elements[elements.size() - 1]->setText("Controls:", w / 2, 150, true, 24, 255, 255, 255);

	elements.push_back(new ScreenText(window, "./Assets/Staatliches-Regular.ttf", 24));
	elements[elements.size() - 1]->setText("W  = Up.", w / 2, 200, true, 24, 255, 255, 255);

	elements.push_back(new ScreenText(window, "./Assets/Staatliches-Regular.ttf", 24));
	elements[elements.size() - 1]->setText("A = Left.", w / 2, 250, true, 24, 255, 255, 255);

	elements.push_back(new ScreenText(window, "./Assets/Staatliches-Regular.ttf", 24));
	elements[elements.size() - 1]->setText("S = Down.", w / 2, 300, true, 24, 255, 255, 255);

	elements.push_back(new ScreenText(window, "./Assets/Staatliches-Regular.ttf", 24));
	elements[elements.size() - 1]->setText("D = Right.", w / 2, 350, true, 24, 255, 255, 255);

	elements.push_back(new ScreenText(window, "./Assets/Staatliches-Regular.ttf", 24));
	elements[elements.size() - 1]->setText("Left click on the mouse is to shoot.", w / 2, 400, true, 24, 255, 255, 255);

	elements.push_back(new ScreenText(window, "./Assets/Staatliches-Regular.ttf", 24));
	elements[elements.size() - 1]->setText("Mouse cursor to aim.", w / 2, 450, true, 24, 255, 255, 255);

	elements.push_back(new ScreenText(window, "./Assets/Staatliches-Regular.ttf", 24));
	elements[elements.size() - 1]->setText("Press ENTER to start playing.", w / 2, 500, true, 30, 1, 255, 1);
}

SplashScreen::~SplashScreen()
{}

void SplashScreen::Input(SDL_Event* event, bool* gamePlaying)
{
	if (event->type == SDL_KEYDOWN && event->key.repeat == 0)//if key is pressed 
	{
		switch (event->key.keysym.sym)
		{
		//space to continue
		case SDLK_RETURN:
			*gamePlaying = true;
			break;
		}
	}
}

void SplashScreen::Update()
{}

void SplashScreen::Render()
{
	for (int i = 0; i < elements.size(); i++)
		elements[i]->render();
}