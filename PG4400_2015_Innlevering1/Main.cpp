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
	std::vector<std::string> texturePathList;
	std::shared_ptr<EventHandler> eventHandler = EventHandler::GetInstance();
	std::shared_ptr<InputManager> inputManager = InputManager::GetInstance();
	SDL_Window *window = SDL_CreateWindow("Test.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_ShowCursor(false);
	if (renderer == NULL)
		std::cout << "renderer creation failed." << std::endl;

	Drawable::Init(renderer);
	SDL_Rect rect;
	rect.x = 100;
	rect.y = 550;
	rect.w = 100;
	rect.h = 25;

	Player player(rect);
	Ball ball;
	
	player.paddle.loadResource("../Resources/Bats/paddle0001.png");
	eventHandler->update();

	while (!eventHandler->exitGame)
	{
		if (inputManager->KeyDown(SDL_SCANCODE_Q))
			eventHandler->exitGame = true;

		// logic
		eventHandler->update();
		player.Update();
		ball.Update ();
		// Draw
		SDL_RenderClear(renderer);
		player.Draw();
		ball.Draw();
		SDL_RenderPresent(renderer);
	}

	return EXIT_SUCCESS;
}