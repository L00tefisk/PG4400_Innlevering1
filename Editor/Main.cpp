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
		b.rect.w = 1280/16;
		b.rect.h = b.rect.w / 2;

		if (b.textureID == 0)
			b.type = 0;
		else if (b.textureID >= 1 && b.textureID <= 3)
			b.type = 1;
		else if (b.textureID == 4)
			b.type = 2;
		if (inputManager->KeyDown(SDL_SCANCODE_LSHIFT))
		{
			b.rect.x = inputManager->getMouseX() / b.rect.w * b.rect.w; // Here I (ab?)use the rounding
			b.rect.y = inputManager->getMouseY() / b.rect.h * b.rect.h; // to lock them to a grid.
		}
		else if(inputManager->KeyDown(SDL_SCANCODE_LCTRL)) {
			b.rect.x = inputManager->getMouseX() / (b.rect.w / 2) * (b.rect.w / 2); // Here I (ab?)use the rounding
			b.rect.y = inputManager->getMouseY() / b.rect.h * b.rect.h; // to lock them to a grid.
		}
		else
		{
			b.rect.x = inputManager->getMouseX();
			b.rect.y = inputManager->getMouseY();
		}


		if (inputManager->KeyDown(SDL_SCANCODE_Q))
			eventHandler->exitGame = true;

		if (inputManager->getMouseButton(1))
		{
			editor->AddBrick(b);
		}
		if (inputManager->KeyNonRepeat(SDL_SCANCODE_E))
			editor->changeBrickID(false);
		else if (inputManager->KeyNonRepeat(SDL_SCANCODE_R))
			editor->changeBrickID(true);
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
			editor->draw();
			SDL_RenderCopy(renderer, Drawable::textureList[editor->currentBrickID], NULL, &b.rect);
			SDL_RenderPresent(renderer);
		}
		
	}
	editor->SaveLevel();
	return EXIT_SUCCESS;
}