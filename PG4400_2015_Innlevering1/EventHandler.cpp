#include "EventHandler.h"

std::shared_ptr<EventHandler> EventHandler::instance = 0;

EventHandler::EventHandler()
{
	inputManagerInstance = InputManager::GetInstance();
	exitGame = false;
}

std::shared_ptr<EventHandler> EventHandler::GetInstance()
{
	if (instance == 0)
		instance = std::shared_ptr<EventHandler>(new EventHandler);
	return instance;
}

void EventHandler::update()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
			exitGame = true;
			
		else if (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP || // Keyboard events
			ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_MOUSEBUTTONUP ||  // Mouse events
			ev.type == SDL_MOUSEMOTION || ev.type == SDL_MOUSEWHEEL)
			processInputEvent(ev);
		else if (ev.type == SDL_WINDOWEVENT)
			processWindowEvent(ev);
	}
}

void EventHandler::processInputEvent(SDL_Event &ev)
{
	inputManagerInstance->update(ev);
}

void EventHandler::processWindowEvent(SDL_Event &ev)
{
	// to be implemented
}