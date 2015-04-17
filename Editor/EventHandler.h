#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <iostream>
#include <SDL.h>
#include <memory>

#include "InputManager.h"


// Event handlers constructor has to be called before using any of the managers.

class EventHandler
{
public:
	static std::shared_ptr<EventHandler> GetInstance();
	void init();
	void update();
	bool exitGame;
private:
	EventHandler();

	static std::shared_ptr<EventHandler> instance;
	std::shared_ptr<InputManager> inputManagerInstance;
	void processInputEvent(SDL_Event &ev);
	void processWindowEvent(SDL_Event &ev);
};

#endif