#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <array>

#include "EventHandler.h"
#include "GameObject.h"
#include "Player.h"


int main(int argc, char* argv[])
{
	std::vector<std::string> texturePathList;
	std::shared_ptr<EventHandler> eventHandler = EventHandler::GetInstance();
	std::shared_ptr<InputManager> inputManager = InputManager::GetInstance();
	SDL_Window *window = SDL_CreateWindow("Test.", 100, 100, 400, 400, NULL);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL, NULL);

	texturePathList.push_back(std::string("../Resources/Bats/paddle0001.png"));

	Drawable::Init(texturePathList, window, renderer);

	Player player;

	eventHandler->update();

	while (!eventHandler->exitGame)
	{
		if (inputManager->KeyDown(SDL_SCANCODE_Q))
			eventHandler->exitGame = true;

		// logic
		eventHandler->update();
		player.Update();

		// Draw
		SDL_RenderClear(renderer);

		player.Draw();

		SDL_RenderPresent(renderer);
	}

	return EXIT_SUCCESS;
}