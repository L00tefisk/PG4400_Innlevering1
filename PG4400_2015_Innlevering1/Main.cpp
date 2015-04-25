#include "GameManager.h"
#include <SDL_ttf.h>
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Test.", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if (window == NULL)
		std::cout << "Window creation failed" << std::endl;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		std::cout << "renderer creation failed." << std::endl;

	if (TTF_Init())
	{
		std::cout << "Failed to initialize SDL_ttf" << std::endl;
	}
	Drawable::Init(renderer);
	GameManager GameManager(window, renderer);
	
	
	SDL_ShowCursor(false);

	GameManager.Init();
	GameManager.Run();
	
	TTF_Quit();
	return 0;
}