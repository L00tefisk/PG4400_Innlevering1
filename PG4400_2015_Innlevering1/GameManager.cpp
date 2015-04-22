#include "GameManager.h"


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
	ball.Init();
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

int getSide(const SDL_Rect &ball, const SDL_Rect &brick)
{
	float ballCenterX = ball.x + ball.w / 2;
	float ballCenterY = ball.y + ball.h / 2;
	float brickCenterX = brick.x + ball.w / 2;
	float brickCenterY = brick.y + ball.h / 2;

	float deltaX = ballCenterX - brickCenterX;
	float deltaY = ballCenterY - brickCenterY;

	deltaY *= 3;

	if (deltaX > deltaY) // left or right
	{
		if (deltaX < 0) // right
			return 2;
		else // left;
			return 4;
		
	}
	else // top or bottom
	{
		if (deltaY < 0) // top
			return 1;
		else if(deltaY > 0) // bottom
			return 3;
	}
	return 0;
}

int getDirection(int side)
{
	if (side == 1 || side == 3)
		return 1;
	else if (side == 2 || side == 4)
		return 2;

	// shouldn't happen.
	return 0;
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

			
			for (Brick b : *level.getMap())
			{
				int collisionStatus = ball.Collide(b, dt / 1000);
				if (collisionStatus)
				{
					SDL_Rect leftBlock, rightBlock, aboveBlock, belowBlock;
					float distLeftBlock, distRightBlock, distAboveBlock, distBelowBlock, distCollBlock;
					distLeftBlock = distRightBlock = distAboveBlock = distBelowBlock = 9001;
					int closestBlock = 0;

					leftBlock = rightBlock = aboveBlock = belowBlock = b.getRectangle();

					leftBlock.x += leftBlock.w;
					rightBlock.x -= rightBlock.w;
					aboveBlock.y -= aboveBlock.h;
					belowBlock.y += belowBlock.h;

					distCollBlock = ((b.getRectangle().x + (b.getRectangle().w / 2)) - (ball.getRectangle().x + (ball.getRectangle().w / 2))) +
   						((b.getRectangle().y + (b.getRectangle().h / 2)) - (ball.getRectangle().y + (ball.getRectangle().h / 2)));

					if (level.hasBrick(leftBlock))
						distLeftBlock = ((leftBlock.x + (leftBlock.w / 2)) - (ball.getRectangle().x + (ball.getRectangle().w / 2))) +
						((leftBlock.y + (leftBlock.h / 2)) - (ball.getRectangle().y + (ball.getRectangle().h / 2)));

					if (level.hasBrick(rightBlock))
						distRightBlock = ((rightBlock.x + (rightBlock.w / 2)) - (ball.getRectangle().x + (ball.getRectangle().w / 2))) +
						((rightBlock.y + (rightBlock.h / 2)) - (ball.getRectangle().y + (ball.getRectangle().h / 2)));

					if (level.hasBrick(aboveBlock))
						distAboveBlock = ((aboveBlock.x + (aboveBlock.w / 2)) - (ball.getRectangle().x + (ball.getRectangle().w / 2))) +
						((aboveBlock.y + (aboveBlock.h / 2)) - (ball.getRectangle().y + (ball.getRectangle().h / 2)));

					if (level.hasBrick(belowBlock))
						distBelowBlock = ((belowBlock.x + (belowBlock.w / 2)) - (ball.getRectangle().x + (ball.getRectangle().w / 2))) +
						((belowBlock.y + (belowBlock.h / 2)) - (ball.getRectangle().y + (ball.getRectangle().h / 2)));

					if (distLeftBlock < distRightBlock &&
						distLeftBlock < distAboveBlock &&
						distLeftBlock < distBelowBlock &&
						distLeftBlock < distCollBlock)
						closestBlock = 0;
					else if (
						distRightBlock < distAboveBlock &&
						distRightBlock < distBelowBlock &&
						distRightBlock < distCollBlock)
						closestBlock = 1;
					else if (
						distAboveBlock < distBelowBlock &&
						distAboveBlock < distCollBlock)
						closestBlock = 2;
					else if (distBelowBlock < distCollBlock)
						closestBlock = 3;
					else
						closestBlock = 4;

					int side = -1;
					switch (closestBlock)
					{
					case 0: // left
						side = getSide(ball.getRectangle(), leftBlock);
						break;
					case 1: // right
						side = getSide(ball.getRectangle(), rightBlock);
						break;
					case 2: // above
						side = getSide(ball.getRectangle(), aboveBlock);
						break;
					case 3: // below
						side = getSide(ball.getRectangle(), belowBlock);
						break;
					case 4: // the block we collided with
						side = getSide(ball.getRectangle(), b.getRectangle());
						break;
					}
					int direction = getDirection(side);

					if (direction == 1)
						ball.ySpeed = -ball.ySpeed;
					else if (direction == 2)
						ball.xSpeed = -ball.xSpeed;

					level.RemoveBrick(b);
					break;

				}

				/*
				if (collisionStatus == 1) // top or bottom
				{
					SDL_Rect tempRect = ball.getRectangle();
	
					if (ball.ySpeed > 0)
						tempRect.y = b.getRectangle().y;
					else
						tempRect.y = b.getRectangle().y + b.getRectangle().h;
					ball.setRectangle(tempRect);

					ball.ySpeed = -ball.ySpeed;
					level.RemoveBrick(b);
					break;
				}
				else if (collisionStatus == 2) // left or right
				{
					SDL_Rect tempRect = ball.getRectangle();
					if (ball.xSpeed > 0)
						tempRect.x = b.getRectangle().x;
					else
						tempRect.x = b.getRectangle().x + b.getRectangle().w;
	
					ball.xSpeed = -ball.xSpeed;
					level.RemoveBrick(b);
					break;
				}
				else if (collisionStatus == 3)
				{
					SDL_Rect tempRect = b.getRectangle();
					Brick tempBrick;
					if (ball.ySpeed > 0) // Top
					{
						tempBrick = Brick(tempRect.x, tempRect.y + tempRect.h, tempRect.w, tempRect.h);
						if (level.hasBrick(tempBrick))
						{
							if (ball.xSpeed > 0)
								tempRect.x = b.getRectangle().x;
							else
								tempRect.x = b.getRectangle().x + b.getRectangle().w;

							ball.xSpeed = -ball.xSpeed;
						}
						else
						{
							if (ball.ySpeed > 0)
								tempRect.y = b.getRectangle().y;
							else
								tempRect.y = b.getRectangle().y + b.getRectangle().h;

							ball.ySpeed = -ball.ySpeed;
						}
					}
					else// bottom
					{
						tempBrick = Brick(tempRect.x, tempRect.y - tempRect.h, tempRect.w, tempRect.h);
						if (level.hasBrick(tempBrick))
						{
							if (ball.xSpeed > 0)
								tempRect.x = b.getRectangle().x;
							else
								tempRect.x = b.getRectangle().x + b.getRectangle().w;

							ball.xSpeed = -ball.xSpeed;
						}
						else
						{
							if (ball.ySpeed > 0)
								tempRect.y = b.getRectangle().y;
							else
								tempRect.y = b.getRectangle().y + b.getRectangle().h;

							ball.ySpeed = -ball.ySpeed;
						}
					}


				}*/
			}
			
			int collisionStatus = ball.Collide(player.paddle, dt / 1000);

			if (collisionStatus == 1)
				ball.ySpeed = -ball.ySpeed;
			else if (collisionStatus == 2)
				ball.xSpeed = -ball.xSpeed;

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