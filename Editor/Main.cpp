// Editor for BreakOut Clone 

/*

	  ==== SAVE FILE STRUCTURE ====
- Position on the X axis,	unsigned integer.
- Position on the Y axis,	unsigned integer.
- The type of the block,	unsigned short.

*/

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <array>

#include "EventHandler.h"
#include "GameObject.h"
#include "Player.h"
#include "Ball.h"
#include "Editor.h"

int main(int argc, char* argv[])
{
	Uint32 time = 0;
	Uint32 previousTime = 0;
	Uint32 dt = 0;
	double fps = (1 / 60.0) * 1000;
	double accumulator = 0.0;
	int frames = 0;
	bool mouseButtonLock = false;

	std::vector<std::string> texturePathList;
	std::shared_ptr<EventHandler> eventHandler = EventHandler::GetInstance();
	std::shared_ptr<InputManager> inputManager = InputManager::GetInstance();
	SDL_Window *window = SDL_CreateWindow("Test.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		std::cout << "renderer creation failed." << std::endl;
	Drawable::Init(renderer);
	Drawable::loadAllTextures();
	eventHandler->update();

	Editor* editor = Editor::GetInstance();
	editor->loadLevel();
	while (!eventHandler->exitGame)
	{
		previousTime = time;
		time = SDL_GetTicks();
		dt = time - previousTime;
		accumulator += dt;

		eventHandler->update();
		
		Brick b;
		b.textureID = editor->currentBrickID;
		if (inputManager->KeyDown(SDL_SCANCODE_LSHIFT))
		{
			b.rect.x = inputManager->getMouseX() / 40 * 40;
			b.rect.y = inputManager->getMouseY() / 10 * 10;
		}
		else
		{
			b.rect.x = inputManager->getMouseX();
			b.rect.y = inputManager->getMouseY();
		}
		b.rect.w = 40;
		b.rect.h = 10;

		if (inputManager->KeyDown(SDL_SCANCODE_Q))
			eventHandler->exitGame = true;

		if (inputManager->getMouseButton(1) && !mouseButtonLock)
		{

			editor->AddBrick(b);
			mouseButtonLock = true;
		}
		else if (!inputManager->getMouseButton(1))
			mouseButtonLock = false;
		if (inputManager->getMouseButton(3))
		{
			editor->RemoveBrick(inputManager->getMouseX(), inputManager->getMouseY());
		}


		if (accumulator >= fps)
		{
			frames++;
			accumulator -= fps;

			// Draw
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, Drawable::textureList[0], NULL, &b.rect);
			editor->draw();
			SDL_RenderPresent(renderer);
		}
		
	}
	editor->SaveLevel();
	return EXIT_SUCCESS;
}