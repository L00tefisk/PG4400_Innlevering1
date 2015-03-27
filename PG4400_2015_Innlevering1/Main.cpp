#include <iostream>
#include <SDL.h>

#include "EventHandler.h"
#include "GameObject.h";

int main(int argc, char* argv[])
{
	EventHandler *eventHandler = EventHandler::GetInstance();
	InputManager *inputManager = InputManager::GetInstance();

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "Failed to initialize SDL, details:" << SDL_GetError() << std::endl;

		return EXIT_FAILURE;
	}

	SDL_Window* window = SDL_CreateWindow(
		"An awesome SDL window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL)
	{
		std::cerr << "Failed to open SDL window, details:" << SDL_GetError() << std::endl;
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		std::cerr << "Failed to create renderer, details:" << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
		return EXIT_FAILURE;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Surface* image = SDL_LoadBMP("sdl2.bmp");
	

	if (image == NULL)
	{
		std::cerr << "Failed to load image, details:" << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		return EXIT_FAILURE;
	}

	SDL_Surface* sdlBro = SDL_LoadBMP("sdl_bro.bmp");
	if (sdlBro == NULL)
	{
		std::cerr << "Failed to load image, details:" << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		return EXIT_FAILURE;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	if (texture == NULL)
	{
		std::cerr << "Failed to generate texture, details:" << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_FreeSurface(image);
		return EXIT_FAILURE;
	}

	SDL_Texture* sdlBroTex = SDL_CreateTextureFromSurface(renderer, sdlBro);
	if (sdlBroTex == NULL)
	{
		std::cerr << "Failed to generate texture, details:" << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_FreeSurface(sdlBro);
		return EXIT_FAILURE;
	}

	SDL_Rect bounding_box;
	bounding_box.h = image->h;
	bounding_box.w = image->w;
	bounding_box.x = 0;
	bounding_box.y = 0;

	SDL_FreeSurface(image);

	SDL_Rect broBox;

	broBox.h = sdlBro->h;
	broBox.w = sdlBro->w;
	broBox.x = 0;
	broBox.y = 0;

	SDL_FreeSurface(sdlBro);
	
	eventHandler->update();
	while (!eventHandler->exitGame)
	{
		if (inputManager->KeyDown(SDL_SCANCODE_Q))
			eventHandler->exitGame = true;

		eventHandler->update();

		broBox.x = inputManager->getMouseX() - broBox.w/2;
		broBox.y = inputManager->getMouseY() - broBox.h/2;

		
		SDL_RenderCopy(renderer, texture, NULL, &bounding_box);
		SDL_RenderCopy(renderer, sdlBroTex, NULL, &broBox);
		SDL_RenderPresent(renderer);
	}
	// ---------------------------------------
	// Game loop would normally run from here.

	// TODO: 1) Get input.

	// TODO: 2) Do business (domain) logic.

	// 3) Render output:


	// Game loop would normally end here.
	// ---------------------------------------

	std::cout << "Everything went better than expected!" << std::endl;
	

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}