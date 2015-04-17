#include "GameManager.h"


GameManager::GameManager(SDL_Window *window, SDL_Renderer *renderer)
{
	this->window = window;
	this->renderer = renderer;

	logicTimer = Timer((1 / 60.0) * 1000); // multiplied by 1000 because we want it in milliseconds
	drawTimer = Timer((1 / 60.0) * 1000);
	level = Level();
	run = true;
};
GameManager::~GameManager()
{

};

void GameManager::Init()
{
	eventHandler = EventHandler::GetInstance();
	inputManager = InputManager::GetInstance();

	
	gameState = MAINMENU;
}

void GameManager::SetupGame()
{
	SDL_Rect rect;
	rect.x = 100;
	rect.y = 600;
	rect.w = 100;
	rect.h = 25;

	player = Player(rect);
	level.loadLevel();
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

bool CollisionCheck(GameObject a, GameObject b)
{
	if (a.getRectangle().x + a.getRectangle().w > b.getRectangle().x &&
		a.getRectangle().y + a.getRectangle().h > b.getRectangle().y &&
		a.getRectangle().x < b.getRectangle().x + b.getRectangle().w &&
		a.getRectangle().y < b.getRectangle().y + b.getRectangle().h)
	{
		return true;
	}
	return false;
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
		if (inputManager->getMouseButton(1))
			ball.Fire();
		while (logicTimer.accumulator >= logicTimer.updateRate)
		{
			logicTimer.accumulator -= logicTimer.updateRate;

			player.Update();
			ball.Update(dt/1000);

			for (Brick b : level.map)
			{
				if (CollisionCheck(ball, b))
				{
					if (ball.centerY < b.getRectangle().y || // Top
						ball.centerY > b.getRectangle().y + b.getRectangle().h) // bottom
						ball.ySpeed = -ball.ySpeed;
					else
						ball.xSpeed = -ball.xSpeed;
					
					level.RemoveBrick(b.getRectangle().x, b.getRectangle().y);
					
					std::cout << "Flip!" << std::endl;
					break;
				}
			}
			
			if (CollisionCheck(ball, player.paddle))
			{
				ball.ySpeed = -ball.ySpeed;
			}
			draw = true;
		}

		if (draw)
		{
			draw = false;
			// Draw
			SDL_RenderClear(renderer);
			player.Draw();
			ball.Draw();
			level.draw();
			SDL_RenderPresent(renderer);
		}
		SDL_Delay(1);
	}
	
}


int selection = 0;

void GameManager::MainMenu()
{
	if (inputManager->KeyNonRepeat(SDL_SCANCODE_DOWN))
	{
		if (--selection < 0)
			selection = 3;

		switch (selection)
		{
		case 0:
			std::cout << "Play." << std::endl;
			break;
		case 1:
			std::cout << "Options." << std::endl;
			break;
		case 2:
			std::cout << "Highscore." << std::endl;
			break;
		case 3:
			std::cout << "Exit." << std::endl;
			break;
		}
	}
	else if (inputManager->KeyNonRepeat(SDL_SCANCODE_UP))
	{
		if (++selection > 3)
			selection = 0;

		switch (selection)
		{
		case 0:
			std::cout << "Play." << std::endl;
			break;
		case 1:
			std::cout << "Options." << std::endl;
			break;
		case 2:
			std::cout << "Highscore." << std::endl;
			break;
		case 3:
			std::cout << "Exit." << std::endl;
			break;
		}
	}

	if (inputManager->KeyDown(SDL_SCANCODE_RETURN))
	{
		switch (selection)
		{
		case 0:
			gameState = PLAY;
			break;
		case 1:
			std::cout << "Options." << std::endl;
			break;
		case 2:
			std::cout << "Highscore." << std::endl;
			break;
		case 3:
			gameState = EXIT;
			break;
		}
	}
	SDL_Delay(15);
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