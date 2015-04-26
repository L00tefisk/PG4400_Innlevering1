#include "GameManager.h"
#include "Vector2D.h"

SDL_Renderer *GameManager::renderer;
SDL_Window *GameManager::window;
Player GameManager::player;
std::vector<Ball> GameManager::balls;

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
const SDL_Rect& GameManager::GetWindowRectangle()
{
	int w, h;
	SDL_Rect winSize;
	SDL_GetWindowSize(window, &w, &h);
	winSize.x = 0;
	winSize.y = 0;
	winSize.w = w;
	winSize.h = h;
	return winSize;
}

void GameManager::SetupGame(std::string nextLevel)
{
	level.loadLevel(nextLevel.c_str());
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

		if (eventHandler->quit || inputManager->KeyDown(SDL_SCANCODE_Q))
			run = false;

		switch (gameState)
		{
		case MAINMENU:
			MainMenu();
			break;
		case PLAY:
			
			if (!Play(logicTimer.updateRate, "test"))
				gameState = MAINMENU;
			else if (!Play(logicTimer.updateRate, "test"))
				gameState = MAINMENU;
			else if (!Play(logicTimer.updateRate, "test"))
				gameState = MAINMENU;

			gameState = MAINMENU;
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

bool GameManager::Play(const double dt, std::string levelName)
{
	SetupGame(levelName);
	bool draw = false;
	std::vector<Brick> &map = level.getMap();
	Vector2D overlapVector;
	Vector2D normalizedVector;
	SDL_Rect ballRect;

	while (true)
	{
		if (level.isDone())
			return true;

		if (player.lives == 0)
			return false;

		logicTimer.Update();
		eventHandler->update();

		if (inputManager->KeyDown(SDL_SCANCODE_Q))
		{
			run = false;
			return false;
		}

		if (inputManager->getMouseButton(1))
		{
			for (Ball &ball : balls)
				ball.Fire();
		}

		while (logicTimer.accumulator >= logicTimer.updateRate)
		{

			logicTimer.accumulator -= logicTimer.updateRate;
			
			if (logicTimer.accumulator > logicTimer.updateRate * 3)
				logicTimer.accumulator = 0;

			player.Update(logicTimer.updateRate);
			const SDL_Rect& paddle = player.getRectangle();
			

			for (int i = 0; i < balls.size(); i++)
			{
				Ball &ball = balls[i];
				ball.Update(dt / 1000);

				ballRect = balls[i].getRectangle();
				// Is the ball colliding with the paddle?
				overlapVector = ball.Collide(player);

				if (overlapVector.magnitude() != 0)
				{
					normalizedVector = overlapVector.getNormalizedVector();
					
					ball.ResolveCollision(overlapVector);
					
					double mod = ((ball.centerX - paddle.x - paddle.w / 2) / paddle.w) * 1000;
					
					if (abs(normalizedVector.x) > abs(normalizedVector.y))
					{
						ball.ySpeed = -ball.ySpeed;
						ball.xSpeed = mod;
					}
				}

				// Is it colliding with any of the bricks?
				for (auto &b : map)
				{
					overlapVector = ball.Collide(b);
					if (overlapVector.magnitude() != 0)
					{
						normalizedVector = overlapVector.getNormalizedVector();
						if (abs(normalizedVector.x) < abs(normalizedVector.y))
							ball.xSpeed = -ball.xSpeed;
						else
							ball.ySpeed = -ball.ySpeed;

						ball.ResolveCollision(overlapVector);

						if (b.Crack())
						{
							PowerUp pow(static_cast<PowerUp::powerType>(rand() % 9), b.getRectangle());
							level.spawnPowerUp(pow);
							level.RemoveBrick(b);
						}
						break;
					}
				}
				if (ballRect.x < 0 || ballRect.x + ballRect.w > 1280) // Did it hit the left or right side?
					ball.xSpeed *= -1;
				else if (ballRect.y + ballRect.h < 0) // did it hit the top or bottom?
					ball.ySpeed *= -1;
				else if (ballRect.y >= 720)
				{
					balls.erase(balls.begin() + i);
					if (balls.size() == 0)
					{
						player.lives--;
						Ball::AddBall(true);
					}
				}
			}

			for (auto it = level.pMap.begin(); it != level.pMap.end();)
			{
				it->Update(dt / 1000);
				if (it->getRectangle().y > 800)
					it = level.pMap.erase(it);
				else
				{
					overlapVector = it->Collide(player);
					if (overlapVector.magnitude() != 0)
					{
						player.ApplyPowerUp(it->type);
						it = level.pMap.erase(it);
					}
					else
						it++;
				}
			}

			draw = true;

		}

		if (draw)
		{
			draw = false;
			// Draw
			SDL_RenderClear(renderer);
			level.draw();
			player.Draw();
			
			for (Ball &ball : balls)
				ball.Draw();

			SDL_RenderPresent(renderer);
		}
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
	//SDL_Delay(15);
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

void GameManager::ChangeLevel()
{
	balls.clear();
}