#include "GameManager.h"

int main(int argc, char* argv[])
{
	//SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Test.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	if (window == NULL)
		std::cout << "Window creation failed" << std::endl;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		std::cout << "renderer creation failed." << std::endl;
	Drawable::Init(renderer);
	GameManager GameManager(window, renderer);
	
	
	SDL_ShowCursor(false);

	GameManager.Init();
	GameManager.Run();
	
	return 0;
}