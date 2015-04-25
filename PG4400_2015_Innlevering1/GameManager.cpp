#include "GameManager.h"
#include "Vector2D.h"

GameManager::GameManager(SDL_Window *window, SDL_Renderer *renderer)
{
	this->window = window;
	this->renderer = renderer;

	logicTimer = Timer((1 / 60.0) * 1000); // multiplied by 1000 because we want it in milliseconds
	drawTimer = Timer((1 / 60.0) * 1000);
	level = Level();
	run = true;

	eventHandler = EventHandler::GetInstance();
	inputManager = InputManager::GetInstance();


	gameState = MAINMENU;
};
GameManager::~GameManager()
{

};

void GameManager::Init()
{

}

void GameManager::SetupGame()
{
	level.loadLevel();
	player.Init();
	Ball::AddBall(true);
	
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

bool GameManager::Play(const double dt)
{
	bool draw = false;
	
	while (true)
	{
		logicTimer.Update();
		eventHandler->update();
		if (inputManager->KeyDown(SDL_SCANCODE_Q))
		{
			run = false;
			return false;
		}
		if (inputManager->getMouseButton(1))
		{
			for (Ball &ball : Ball::balls)
				ball.Fire();
		}
		while (logicTimer.accumulator >= logicTimer.updateRate)
		{
			logicTimer.accumulator -= logicTimer.updateRate;

			player.Update();
			for (Ball &ball : Ball::balls)
			{
				ball.Update(dt / 1000);


				for (Brick b : *level.getMap())
				{
					Vector2D overlapVector = ball.Collide(b);
					if (overlapVector.magnitude() != 0)
					{
						SDL_Rect ballRect = ball.getRectangle();
						Vector2D normalizedVector = overlapVector.getNormalizedVector();
						if (abs(normalizedVector.x) <= abs(normalizedVector.y))
							ball.xSpeed = -ball.xSpeed;
						else
							ball.ySpeed = -ball.ySpeed;

						if (abs(overlapVector.x) <= abs(overlapVector.y))
							ballRect.x += overlapVector.x;
						else
							ballRect.y += overlapVector.y;

						ball.setRectangle(ballRect);

						if (b.Crack())
						{
							PowerUp pow(static_cast<PowerUp::powerType>(rand() % 9), b.getRectangle());
							level.spawnPowerUp(pow);
							level.RemoveBrick(b);
						}
						break;
					}
				}

				Vector2D overlapVector = ball.Collide(player.paddle);

				if(overlapVector.magnitude() != 0) {
					Vector2D normalizedVector = overlapVector.getNormalizedVector();
					const SDL_Rect& paddle = player.paddle.getRectangle();
					double mod = ((ball.centerX - paddle.x - paddle.w / 2) / paddle.w) * 1000;
					if(abs(normalizedVector.x) > abs(normalizedVector.y))
					{
						ball.ySpeed = -ball.ySpeed;
						ball.xSpeed = mod;
					}
						
					//else
					//	ball.xSpeed = -ball.xSpeed;
					SDL_Rect ballRect = ball.getRectangle();
					if(abs(overlapVector.x) < abs(overlapVector.y))
						ballRect.x += overlapVector.x;
					else
						ballRect.y += overlapVector.y;
					ball.setRectangle(ballRect);
				}
			}

			for (auto it = level.pMap.begin(); it != level.pMap.end();)
			{
				it->Update(dt / 1000);
				Vector2D overlapVector = it->Collide(player.paddle);
				if (overlapVector.magnitude() != 0)
				{
					if(it->type == PowerUp::powerType::Shrink && player.paddle.getRectangle().w >= 50)
						const_cast<SDL_Rect&>(player.paddle.getRectangle()).w -= 40;
					if(it->type == PowerUp::powerType::Grow && player.paddle.getRectangle().w <= 300)
						const_cast<SDL_Rect&>(player.paddle.getRectangle()).w += 40;
					Ball::ApplyPowerUp(it->type);
					it = level.pMap.erase(it);
				}
				else
					it++;
			}

			if (level.getMap()->size() == 0)
				return true;

			draw = true;

		}

		if (draw)
		{
			draw = false;
			// Draw
			SDL_RenderClear(renderer);
			player.Draw();
			
			for (Ball &ball : Ball::balls)
				ball.Draw();

			level.draw();
			SDL_RenderPresent(renderer);
		}
		SDL_Delay(1);
	}
	return false;
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