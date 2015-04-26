#include "GameManager.h"
#include "Vector2D.h"
#include <time.h>
SDL_Renderer *GameManager::renderer;
SDL_Window *GameManager::window;
Player GameManager::player;
std::vector<Ball> GameManager::balls;

GameManager::GameManager(SDL_Window *window, SDL_Renderer *renderer)
{
	GameManager::window = window;
	GameManager::renderer = renderer;

	logicTimer = Timer((1 / 60.0) * 1000); // multiplied by 1000 because we want it in milliseconds
	drawTimer = Timer((1 / 60.0) * 1000);
	level = Level();
	run = true;

	eventHandler = EventHandler::GetInstance();
	inputManager = InputManager::GetInstance();

	SDL_Rect scr;
	scr.x = 0;
	scr.y = 0;
	scr.w = 1280;
	scr.h = 720;
	menu.loadResource("../Resources/Background/menu.png", scr);
	gameOver.loadResource("../Resources/Background/gameover.png", scr);
	gameState = MAINMENU;
};

GameManager::~GameManager()
{

};

const SDL_Rect& GameManager::GetWindowRectangle()
{
	int w, h;
	SDL_Rect *winSize = new SDL_Rect;
	SDL_GetWindowSize(window, &w, &h);
	winSize->x = 0;
	winSize->y = 0;
	winSize->w = w;
	winSize->h = h;
	return *winSize;
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
			
			if (!Play(logicTimer.updateRate, "../Resources/Levels/park"))
				gameState = GAMEOVER;
			else if (!Play(logicTimer.updateRate, "../Resources/Levels/sunset"))
				gameState = GAMEOVER;
			else if (!Play(logicTimer.updateRate, "../Resources/Levels/tomas")) // <3
				gameState = GAMEOVER;
			else
				gameState = MAINMENU;
			break;
		case GAMEOVER:
			GameOver();
			break;
		case EXIT:
			run = false;
			break;
		}
		
	}
}

void GameManager::SetupGame(const std::string& levelName)
{
	level.loadLevel(levelName.c_str());
	player.Init();
	Ball::AddBall(true);
}

bool GameManager::Play(const double dt, std::string levelName)
{
	SetupGame(levelName);
	bool draw = false;
	std::vector<Brick> &map = level.getMap();
	Vector2D overlapVector;
	Vector2D normalizedVector;
	SDL_Rect ballRect;
	srand(time(NULL));

	while (true)
	{

		if (level.isDone())
		{
			powMap.clear();
			level.getMap().clear();
			balls.clear();
			Ball::Reset();
			return true;
		}

		if (player.lives == 0)
			break;

		logicTimer.Update();
		eventHandler->update();

		if (inputManager->KeyDown(SDL_SCANCODE_Q))
			break;

		if (inputManager->getMouseButton(1))
		{
			for (Ball &ball : balls)
				ball.Fire();
		}

		// This is more accurate, but will crash the program if each frame takes longer than
		// logcitTimer.updateRate to complete.
		while (logicTimer.accumulator >= logicTimer.updateRate)
		{
			logicTimer.accumulator -= logicTimer.updateRate;
			
			player.Update(logicTimer.updateRate);

			const SDL_Rect& paddle = player.getRectangle();
			
			for (unsigned int i = 0; i < balls.size(); i++)
			{
				Ball &ball = balls[i];
				ball.Update(dt / 1000);
				ballRect = balls[i].getRectangle();

				// Is the ball colliding with the paddle?
				overlapVector = ball.Collide(player);
				if (overlapVector.magnitude() != 0)
				{
					normalizedVector = overlapVector.getNormalizedVector();
					ball.relativeHitPositionX = ballRect.x - paddle.x;
					ball.ResolveCollision(overlapVector);
					Vector2D ballCenter = ball.getCenter();

					if (abs(normalizedVector.x) > abs(normalizedVector.y))
					{
						ball.ySpeed *= -1;
						ball.xSpeed = ((ball.getCenter().x - GameManager::player.getCenter().x) / GameManager::player.getRectangle().w ) * 1000;
					}

					if(ball.isPowerUpActive(PowerUp::powerType::Magnet))
						ball.onPaddle = true;
				}

				// Is it colliding with any of the bricks?
				for (auto &b : map)
				{
					overlapVector = ball.Collide(b);
					if (overlapVector.magnitude() != 0)
					{
						if (!ball.isPowerUpActive(PowerUp::powerType::Super))
						{
							normalizedVector = overlapVector.getNormalizedVector();
							if(abs(normalizedVector.x) < abs(normalizedVector.y))
								ball.xSpeed *= -1;
							else
								ball.ySpeed *= -1;

							ball.ResolveCollision(overlapVector);
						}
						if (b.Crack() || ball.isPowerUpActive(PowerUp::powerType::Super))
						{
							if(rand() % 5 == 1) 
							{
								PowerUp pow(static_cast<PowerUp::powerType>(rand() % 8), b.getRectangle());
								powMap.push_back(pow);
							}
							
							if (b.getHP() <= 0 || ball.isPowerUpActive(PowerUp::powerType::Super))
							{
								level.RemoveBrick(b);
								break;
							}
						}
						
					}
					
				}

				// Check against the sides of the screen
				if (ballRect.x < 0)
				{
					ballRect.x = 0;
					ball.xSpeed *= -1;
				}
				else if (ballRect.x + ballRect.w > GameManager::GetWindowRectangle().w)
				{
					ballRect.x = GameManager::GetWindowRectangle().w - ballRect.w;
					ball.xSpeed *= -1;
				}
				else if (ballRect.y < 0)
				{
					ballRect.y = 0;
					ball.ySpeed *= -1;
				}
				else if (ballRect.y >= 720)
				{
					balls.erase(balls.begin() + i);
					if (balls.size() == 0)
					{
						player.lives--;
						Ball::AddBall(true);
						Ball::Reset();
					}
				}
				ball.setRectangle(ballRect);
			}

			// Check against any spawned powerup
			for (auto it = powMap.begin(); it != powMap.end();)
			{
				it->Update(dt / 1000);
				if (it->getRectangle().y > 800)
					it = powMap.erase(it);
				else
				{
					overlapVector = it->Collide(player);
					if (overlapVector.magnitude() != 0)
					{
						player.ApplyPowerUp(it->type);
						it = powMap.erase(it);
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

			SDL_RenderClear(renderer);
			level.draw();
			player.Draw();
			
			for (Ball &ball : balls)
				ball.Draw();

			for (PowerUp &pow : powMap)
				pow.Draw();

			SDL_RenderPresent(renderer);
		}
	}

	powMap.clear();
	level.getMap().clear();
	balls.clear();
	Ball::Reset();
	return false;
}




void GameManager::MainMenu()
{


	if (inputManager->KeyNonRepeat(SDL_SCANCODE_DOWN))
	{
		if (--selection < 0)
			selection = 3;
	}
	else if (inputManager->KeyNonRepeat(SDL_SCANCODE_UP))
	{
		if (++selection > 3)
			selection = 0;
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

	SDL_RenderClear(renderer);
	menu.Draw();
	SDL_RenderPresent(renderer);
}

void GameManager::GameOver()
{
	if (inputManager->KeyDown(SDL_SCANCODE_RETURN))
		gameState = MAINMENU;
	SDL_RenderClear(renderer);
	gameOver.Draw();
	SDL_RenderPresent(renderer);
}