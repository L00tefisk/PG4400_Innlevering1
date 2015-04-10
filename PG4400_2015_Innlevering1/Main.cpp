#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <array>

#include "EventHandler.h"
#include "GameObject.h"
#include "Player.h"
#include "Ball.h"

int main(int argc, char* argv[])
{
	Uint32 time = 0;
	Uint32 previousTime = 0;
	Uint32 dt = 0;
	double fps = (1 / 60.0) * 1000;
	double accumulator = 0.0;
	int frames = 0;

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

	player.paddle.loadResource("../Resources/Bats/paddle0002.png");
	eventHandler->update();


	while (!eventHandler->exitGame)
	{
		previousTime = time;
		time = SDL_GetTicks();
		dt = time - previousTime;
		accumulator += dt;

		if (inputManager->KeyDown(SDL_SCANCODE_Q))
			eventHandler->exitGame = true;

		if (accumulator >= fps)
		{
			frames++;
			accumulator -= fps;

			// logic
			eventHandler->update();
			player.Update();

			// Draw
			SDL_RenderClear(renderer);
			player.Draw();
			
			SDL_RenderPresent(renderer);

			system("cls");
			std::cout << "Frames: " << frames << std::endl;
			std::cout << "Seconds: " << SDL_GetTicks() / 1000.0 << std::endl;
			std::cout << "FPS: " << frames / (SDL_GetTicks() / 1000.0) << std::endl;
		}

	}

	return EXIT_SUCCESS;
}