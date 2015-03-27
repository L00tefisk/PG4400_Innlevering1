#include <iostream>
#include <SDL.h>

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{

		std::cerr << "Failed to initialize SDL, details:" << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	SDL_Window* window = SDL_CreateWindow(
		"An awesome SDL window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		550,
		400,
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

	SDL_Rect bounding_box;
	bounding_box.h = image->h;
	bounding_box.w = image->w;
	bounding_box.x = 0;
	bounding_box.y = 0;

	SDL_FreeSurface(image);

	// ---------------------------------------
	// Game loop would normally run from here.

	// TODO: 1) Get input.

	// TODO: 2) Do business (domain) logic.

	// 3) Render output:
	SDL_RenderCopy(renderer, texture, NULL, &bounding_box);
	SDL_RenderPresent(renderer);

	// Game loop would normally end here.
	// ---------------------------------------
	int c;
	std::cout << "Everything went better than expected!" << std::endl;

	system("pause");

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}