#include "GameManager.h"


GameManager::GameManager(SDL_Window *window, SDL_Renderer *renderer)
{
	this->window = window;
	this->renderer = renderer;

	logicTimer = Timer((1 / 60.0) * 1000); // multiplied by 1000 because we want it in milliseconds
	drawTimer = Timer((1 / 60.0) * 1000);
	currentLevel = Level();
	run = true;
};
GameManager::~GameManager()
{

};

void GameManager::Init()
{
	eventHandler = EventHandler::GetInstance();
	inputManager = InputManager::GetInstance();

	
	gameState = PLAY;
}

void GameManager::SetupGame()
{
	SDL_Rect rect;
	rect.x = 100;
	rect.y = 600;
	rect.w = 100;
	rect.h = 25;

	player = Player(rect);
}

void GameManager::Run()
{
	
	eventHandler->update();

	double seconds = 0;
	double offsetSeconds = 0;
	while (run)
	{
		eventHandler->update();

		if (eventHandler->quit)
			run = false;

		switch (gameState)
		{
		case MAINMENU:
			MainMenu();
			break;
		case PLAY:
			SetupGame();
			Play(logicTimer.updateRate);
			break;
		case OPTIONS:
			Options();
			break;
		case HIGHSCORES:
			Highscores();
			break;
		case EXIT:
			run = false;
			break;
		}
		
	}
}
void GameManager::Play(const double dt)
{
	bool draw = false;
	
	while (true)
	{
		logicTimer.Update();
		eventHandler->update();
		if (inputManager->KeyDown(SDL_SCANCODE_Q))
		{
			run = false;
			return;
		}
		while (logicTimer.accumulator >= logicTimer.updateRate)
		{
			logicTimer.accumulator -= logicTimer.updateRate;

			player.Update();
			ball.Update(dt);


			draw = true;
		}

		if (draw)
		{
			// Draw
			SDL_RenderClear(renderer);
			player.Draw();
			ball.Draw();
			SDL_RenderPresent(renderer);
		}
	}
	
}
void GameManager::MainMenu()
{
	int selection;
	

	// if play
	 // playGame()
	// if options
	 // Options()
	// if highscores
	 // Highscores()
}
void GameManager::Options()
{
	// if back
	 // mainmenu
	// if other shit
	 // mess with other shit
}
void GameManager::Highscores()
{
	// Draw highscores
}