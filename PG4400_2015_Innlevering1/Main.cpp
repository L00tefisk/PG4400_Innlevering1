#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <array>

#include "EventHandler.h"
#include "GameObject.h"
#include "DrawEngine.h"
#include "Player.h"


int main(int argc, char* argv[])
{
	std::shared_ptr<EventHandler> eventHandler = EventHandler::GetInstance();
	std::shared_ptr<InputManager> inputManager = InputManager::GetInstance();
	Player* player = new Player();
	/*SDL_Surface* image = IMG_Load("../Resources/sdl2.bmp");

	std::array<SDL_Texture*, 2> textureArray;

	if (image == NULL)
	{
		std::cerr << "Failed to load image, details:" << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		return EXIT_FAILURE;
	}

	SDL_Surface* sdlBro = SDL_LoadBMP("../Resources/sdl_bro.bmp");

	if (sdlBro == NULL)
	{
		std::cerr << "Failed to load image, details:" << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		return EXIT_FAILURE;
	}

	textureArray[0] = SDL_CreateTextureFromSurface(renderer, image);

	if (textureArray[0] == NULL)
	{
		std::cerr << "Failed to generate texture, details:" << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_FreeSurface(image);
		return EXIT_FAILURE;
	}

	textureArray[1] = SDL_CreateTextureFromSurface(renderer, sdlBro);
	if (textureArray[1] == NULL)
	{
		std::cerr << "Failed to generate texture, details:" << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_FreeSurface(sdlBro);
		return EXIT_FAILURE;
	}
	*/

	SDL_Rect bounding_box;
	bounding_box.h = 1000;//image->h;
	bounding_box.w = 500;//image->w;
	bounding_box.x = 0;
	bounding_box.y = 0;

	//SDL_FreeSurface(image);

	SDL_Rect broBox;

	broBox.h = 50;//sdlBro->h;
	broBox.w = 50;//sdlBro->w;
	broBox.x = 0;
	broBox.y = 0;

	//SDL_FreeSurface(sdlBro);
	
	eventHandler->update();

	while (!eventHandler->exitGame)
	{
		if (inputManager->KeyDown(SDL_SCANCODE_Q))
			eventHandler->exitGame = true;

		player->update();
		eventHandler->update();

		broBox.x = inputManager->getMouseX() - broBox.w/2;
		broBox.y = inputManager->getMouseY() - broBox.h/2;

		//drawEngine->Draw(broBox, "../Resources/sdl_bro.bmp");
	}

	std::cout << "Everything went better than expected!" << std::endl;
	

	//drawEngine->~DrawEngine();

	return EXIT_SUCCESS;
}