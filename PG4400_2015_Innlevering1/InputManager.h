// Accepts input events from the event handler
// and processes them accordingly.

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include <iostream>

class InputManager
{
public:
	static InputManager* GetInstance();
	bool KeyDown(int key);
	int getMouseX();
	int getMouseY();
	
	// redundant?
	bool keyUp(int key);
	bool keyStillDown(int key);
	bool keyStillUp(int key);

	void update(SDL_Event &ev);
private:
	InputManager();

	static InputManager *instance;

	// Keyboard variables
	int keyAmount;
	bool* keys;

	// Mouse variables
	unsigned int x;
	unsigned int y;
	int dY;
	int dX;
	int wheelX;
	int wheelY;

	bool* buttons;

protected:
	bool handleKeyboardEvent(SDL_Event &ev);
	bool handleMouseEvent(SDL_Event &ev);
	bool handleJoystickEvent(SDL_Event &ev);
};

#endif