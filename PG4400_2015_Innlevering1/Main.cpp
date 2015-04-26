#include "GameManager.h"
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window* window = SDL_CreateWindow("Blue Balls", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if (window == NULL)
		std::cout << "Window creation failed" << std::endl;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		std::cout << "renderer creation failed." << std::endl;

	Drawable::Init(renderer);
	GameManager GameManager(window, renderer);
	
	
	SDL_ShowCursor(false);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	GameManager.Run();
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}