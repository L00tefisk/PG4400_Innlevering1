// Accepts input events from the event handler
// and processes them accordingly.

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include <iostream>
#include <memory>
#include <vector>

class InputManager
{
public:
	static std::shared_ptr<InputManager> GetInstance();
	bool KeyDown(int key);
	bool KeyNonRepeat(int key);

	int getMouseX();
	int getMouseY();
	bool getMouseButton(int button);

	void update(SDL_Event &ev);
private:
	InputManager();
	bool handleKeyboardEvent(SDL_Event &ev);
	bool handleMouseEvent(SDL_Event &ev);
	bool handleJoystickEvent(SDL_Event &ev);

	static std::shared_ptr<InputManager> instance;

	// Keyboard variables
	int keyAmount;
	bool *keys;
	std::vector<int> previouslyCheckedKeys;

	// Mouse variables
	bool buttons[6];
	unsigned int x;
	unsigned int y;
	int dY;
	int dX;
	int wheelX;
	int wheelY;

};

#endif