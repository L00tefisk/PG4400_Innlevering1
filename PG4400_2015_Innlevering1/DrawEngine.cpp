#include "DrawEngine.h"
#include <iostream>

DrawEngine::DrawEngine()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "Failed to initialize SDL, details:" << SDL_GetError() << std::endl;
	}
	window = SDL_CreateWindow(
		"An awesome SDL window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1024,
		576,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL)
	{
		std::cerr << "Failed to open SDL window, details:" << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		std::cerr << "Failed to create renderer, details:" << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
	}

	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//SDL_RenderClear(renderer);
}

int DrawEngine::Draw(SDL_Rect locationSizeMap, std::string path)
{
	SDL_RenderClear(renderer);
	std::string respath = "../Resources/";				//NEVER
	respath.append(path);								//EVER
	char fpath[1024];									//DO
	strncpy_s(fpath, respath.c_str(), sizeof(fpath));	//THIS
	fpath[sizeof(fpath) - 1] = 0;						//AGAIN

	SDL_Surface* surface = IMG_Load(fpath);

	if (surface == NULL)
	{
		std::cerr << "Failed to load image, details:" << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
	{
		std::cerr << "Failed to generate texture, details:" << SDL_GetError() << std::endl;
		SDL_FreeSurface(surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_RenderCopy(renderer, texture, NULL, &locationSizeMap);

	SDL_RenderPresent(renderer); // Spør Tomas om vi kan bruke c++11 pointers istadenfor SDL_Renderer*

	return EXIT_SUCCESS;
}

/*DrawEngine::~DrawEngine()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
*/