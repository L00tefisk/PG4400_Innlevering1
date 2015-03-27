#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <iostream>
#include <SDL.h>

#include "InputManager.h"


// Event handlers constructor has to be called before using any of the managers.

class EventHandler
{
public:
	static EventHandler* GetInstance();
	void init();
	void update();
	bool exitGame;
private:
	EventHandler();

	static EventHandler *instance;
	InputManager *inputManagerInstance;
protected:
	void processInputEvent(SDL_Event &ev);
	void processWindowEvent(SDL_Event &ev);
};

#endif