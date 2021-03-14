#include"Game.h"

//main game class
void Game::MainGameLoop()
{
	//creates window
	window = SDL_CreateWindow("Myles Leslie - 15614035, CGP2011M, UFO Invasion.", 300, 300, Width, Height, SDL_WINDOW_RESIZABLE);
	//renders window
	renderer = SDL_CreateRenderer(window, 0, 0);

	//Logging for window works
	if (window == NULL)
	{
		SDL_Log("Window is broken!");
	}
	else
	{
		SDL_Log("Window is working!");
	}

	if (renderer == NULL)
	{
		SDL_Log("Renderer is broken!");
	}
	else
	{
		SDL_Log("Renderer is working!");
	}

	//draws, colours and renders window
	SDL_SetRenderDrawColor(renderer, 0, 0, 20, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	//create player
	Player.Init(PlayerSpawnX, PlayerSpawnY, SqareWidth, SqareHeight, renderer);
	SDL_Log("Player spawns at PlayerSpawnX=%f, PlayerSpawnY=%f!");
	//creates enemy
	EnemySpawn.Init();
	SDL_Log("Enemy spawns!");

	//flags for images
	int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if ((IMG_Init(img_flags) & img_flags) != img_flags)
	{
		SDL_Log("Image is broken!");
	}
	else
	{
		SDL_Log("Image loading!");
	}

	//initialises music - doesn't work due to nuget packages
	TTF_Init();

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		SDL_Log("Warning: Audio has not been found!\n");
	}
	else
	{
		//Music.wav
		backgroundMusic = Mix_LoadMUS("./content/music1.wav");
		Mix_VolumeMusic(32);
	}

	Mix_PlayMusic(backgroundMusic, -1);

	splashScreen = new SplashScreen(window);

	//while game is running
	while (!done)
	{
		Input();
		Update();
		Render();
	}

	Mix_FreeMusic(backgroundMusic);
	Mix_CloseAudio();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Log("Game Quit");
	SDL_Quit();
}

//spawns enemies
void Game::CalculateEnemyPos(int* x, int* y)
{
	int RandomX = rand() % Height;
	int RandomY = rand() % Width;

	//calculate the distance between where the player is so that the enemies will not spawn on the player
	float absDiffX = abs(RandomX - Player.x + 20);
	float absDiffY = abs(RandomY - Player.y + 20);

	//Set the range that they can not spawn in, max is 250 
	if (absDiffY < 60 || absDiffX < 60) {
		return CalculateEnemyPos(x, y);
	}

	//place that they can spawn
	*x = RandomX;
	*y = RandomY;
}

void Game::Input()
{
	//SDL_Log("--- INPUT PHASE ---");

	SDL_Event _event;
	while (SDL_PollEvent(&_event))
	{
		if (gamePlaying)
		{
			Player.Input(&_event);
			SDL_Log("Player moving");
			if (_event.type == SDL_KEYDOWN && _event.key.repeat == 0)
			{
				switch (_event.key.keysym.sym)
				{
				case SDLK_p:
					if (Mix_PlayingMusic() == 0)
						Mix_PlayMusic(backgroundMusic, -1);
					else Mix_HaltMusic();
					break;
				}
			}
		}
		else
		{
			SDL_Log("SplashScreen displayed");
			splashScreen->Input(&_event, &gamePlaying);
		}
	}
}

void Game::Update()
{
	//SDL_Log("--- UPDATE PHASE ---");

	if (gamePlaying)
	{
		//set size of the window
		SDL_GetWindowSize(window, &Width, &Height);
		Player.Update(gameTimer.deltaTime, EnemySpawn.ListofEnemies);
		Player.WindowSize(Height, Width);

		EnemySpawn.WindowSize(Height, Width);

		//calculates random place of enemies
		int CalX, CalY;
		CalculateEnemyPos(&CalX, &CalY);
		EnemySpawn.Add(CalX, CalY, renderer);
		EnemySpawn.Update(gameTimer.deltaTime);

		gameTimer.tick();
		timeRemaining -= gameTimer.timeSinceLastFrame();
	}
	else
	{
		splashScreen->Update();
	}

	//std::cout << "Time Remaining: " << timeRemaining << std::endl;

#ifdef LOG_IN_SECONDS
	if ((int)timeRemaining != lastTimeRemainingSeconds)
	{
		SDL_Log("Time Remaining: %i seconds", lastTimeRemainingSeconds);
		lastTimeRemainingSeconds = (int)timeRemaining;
	}
#else
	SDL_Log("Time Remaining: %f seconds", timeRemaining);
#endif

	if (timeRemaining <= 0.0f)
		done = true;
}

void Game::Render()
{
	//SDL_Log("--- RENDER PHASE ---");

	SDL_SetRenderDrawColor(renderer, 0, 0, 20, SDL_ALPHA_OPAQUE);//render window
	SDL_RenderClear(renderer);

	if (gamePlaying)
	{
		//render player object
		Player.Render(renderer);
		//renders enemy 
		EnemySpawn.Render(renderer);
	}
	else
	{
		splashScreen->Render();
	}
	//show what is rendered
	SDL_RenderPresent(renderer);
}