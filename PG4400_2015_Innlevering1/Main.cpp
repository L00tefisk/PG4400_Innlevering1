#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <array>

#include "EventHandler.h"
#include "GameObject.h"
#include "Player.h"
#include "Ball.h"

class Timer
{
public:
	Timer(double updateRate) :
		updateRate(updateRate),
		time(0),
		previousTime(0),
		dt(0),
		accumulator(0.0){};


	void Update()
	{
		previousTime = time;
		time = SDL_GetTicks();
		dt = time - previousTime;
		accumulator += dt;
	}
	Uint32 time;
	Uint32 previousTime;
	Uint32 dt;
	double updateRate;
	double accumulator;
private:

};

int main(int argc, char* argv[])
{
	Timer logicTimer((1 / 60.0 ) * 1000);
	Timer drawTimer((1 / 60.0) * 1000);
	double logicFrames = 0;
	double drawFrames = 0;
	std::vector<std::string> texturePathList;
	std::shared_ptr<EventHandler> eventHandler = EventHandler::GetInstance();
	std::shared_ptr<InputManager> inputManager = InputManager::GetInstance();
	SDL_Window *window = SDL_CreateWindow("Test.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_ShowCursor(false);
	if (renderer == NULL)
		std::cout << "renderer creation failed." << std::endl;

	Drawable::Init(renderer);
	SDL_Rect rect;
	rect.x = 100;
	rect.y = 700;
	rect.w = 100;
	rect.h = 25;

	Player player(rect);
	Ball ball;
	player.paddle.loadResource("../Resources/Bats/paddle0002.png");
	eventHandler->update();

	double seconds = 0;
	double offsetSeconds = 0;
	while (!eventHandler->exitGame)
	{

		logicTimer.Update();
		drawTimer.Update();
		eventHandler->update();
		if (inputManager->KeyDown(SDL_SCANCODE_Q))
			eventHandler->exitGame = true;

		if (inputManager->KeyDown(SDL_SCANCODE_R))
		{
			logicFrames = 0;
			drawFrames = 0;
			offsetSeconds = SDL_GetTicks();
		}


		while (logicTimer.accumulator >= logicTimer.updateRate)
		{
			logicTimer.accumulator -= logicTimer.updateRate;
			logicFrames++;

			// logic			
			player.Update();
			ball.Update(logicTimer.updateRate);

		}

		//SDL_Delay(100);
		// Draw
		if (drawTimer.accumulator >= drawTimer.updateRate)
		{

			drawFrames++;
			drawTimer.accumulator -= drawTimer.updateRate;

			SDL_RenderClear(renderer);
			player.Draw();
			ball.Draw();
			SDL_RenderPresent(renderer);

			
			system("cls");
			std::cout << "Logical frames: " << logicFrames << std::endl;
			std::cout << "Logical seconds: " << (logicTimer.time - offsetSeconds) << std::endl;
			std::cout << "Logical FPS: " << logicFrames / ((logicTimer.time - offsetSeconds) / 1000 ) << std::endl;

			std::cout << "Program frames: " << drawFrames << std::endl;
			std::cout << "Program seconds: " << drawTimer.time - offsetSeconds << std::endl;
			std::cout << "Program FPS: " << drawFrames / ((drawTimer.time - offsetSeconds) / 1000) << std::endl;
		}
	}

	return EXIT_SUCCESS;
}