#include "InputManager.h"

std::shared_ptr<InputManager> InputManager::instance = 0;

// Public methods
std::shared_ptr<InputManager> InputManager::GetInstance()
{
	if (instance == 0)
		instance = std::unique_ptr<InputManager>(new InputManager);
	return instance;
}
void InputManager::update(SDL_Event &ev)
{
	if (!handleKeyboardEvent(ev))
		if (!handleMouseEvent(ev))
			handleJoystickEvent(ev);	
}
bool InputManager::KeyDown(int key)
{
	return keys[key];
}
int InputManager::getMouseX()
{
	return x;
}
int InputManager::getMouseY()
{
	return y;
}
// Private methods
InputManager::InputManager()
{
	// Keyboard stuff
	keyAmount = 255;
	keys = new bool[keyAmount];
	for (int i = 0; i < 255; i++)
		keys[i] = false;

	// Mouse stuff
	x = y = dX = dY = 0;
	wheelX = wheelY = 0;
	for (int i = 0; i < 6; i++)
		buttons[i] = false;
};

bool InputManager::handleKeyboardEvent(SDL_Event &ev)
{
	if (ev.type == SDL_KEYDOWN)
	{
		std::cout << "Key: " << SDL_GetKeyName(ev.key.keysym.sym) << " was ";
		if (keys[ev.key.keysym.scancode])
			std::cout << "repeated\n";
		else
			std::cout << "pressed\n";
		keys[ev.key.keysym.scancode] = true;
		return true;
	}
	else if (ev.type == SDL_KEYUP)
	{
		std::cout << "Key: " << SDL_GetKeyName(ev.key.keysym.sym) << " was ";
		std::cout << "released\n";
		keys[ev.key.keysym.scancode] = false;
		return true;
	}
	return false;
}
bool InputManager::handleMouseEvent(SDL_Event &ev)
{
	// Most of the time it'll be the mousemotion event
	if (ev.type == SDL_MOUSEMOTION)
	{
		std::cout << "Mouse moved.";
		dX = ev.motion.x - x;
		dY = ev.motion.y - y;
		x = ev.motion.x;
		y = ev.motion.y;
		std::cout << "[ " << x << "," << y << "," << dX << "," << dY << "]\n";
	}
	else if (ev.type == SDL_MOUSEWHEEL)
	{
		wheelX = ev.wheel.x;
		wheelY = ev.wheel.y;

		std::cout << "Mousewheel moved (" << wheelX << "," << wheelY << ") ";
		if (wheelY > 0)
			std::cout << "up.\n";
		else
			std::cout << "down.\n";

	}
	else if (ev.type == SDL_MOUSEBUTTONDOWN)
	{
		std::cout << "mouse button " << (int)ev.button.button << " was clicked.\n";
		buttons[ev.button.button] = true;
	}
	else // Has to be the mousebutton up at this point, no point checking for it.
	{
		std::cout << "mouse button " << (int)ev.button.button << " was released.\n";
		buttons[ev.button.button] = false;
	}
	return true;
}
bool InputManager::handleJoystickEvent(SDL_Event &ev)
{
	// Not implemented yet
	return true;
}