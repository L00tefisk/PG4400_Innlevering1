#include "InputManager.h"

std::shared_ptr<InputManager> InputManager::instance = 0;

// Public methods
std::shared_ptr<InputManager> InputManager::GetInstance()
{
	if (instance == 0)
		instance = std::shared_ptr<InputManager>(new InputManager);
	return instance;
}
void InputManager::update(SDL_Event &ev)
{
	// Doing it this way prevents unnecessary if statements.
	handleKeyboardEvent(ev);
	handleMouseEvent(ev);

}
bool InputManager::KeyDown(int key) const
{
	return keys[key];
}
bool InputManager::KeyNonRepeat(int key)
{
	for (unsigned int i = 0; i < previouslyCheckedKeys.size(); i++)
		if (key == previouslyCheckedKeys[i])
			return false;
	
	if (keys[key])
		previouslyCheckedKeys.push_back(key);

	return keys[key];

}
int InputManager::getMouseX() const
{
	return x;
}
int InputManager::getMouseY() const
{
	return y;
}
bool InputManager::getMouseButton(int button) const
{
	return buttons[button];
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
		keys[ev.key.keysym.scancode] = true;
		return true;
	}
	else if (ev.type == SDL_KEYUP)
	{
		keys[ev.key.keysym.scancode] = false;
		for (auto it = previouslyCheckedKeys.begin(); it != previouslyCheckedKeys.end(); it++)
		{
			if (ev.key.keysym.scancode == *it)
			{
				previouslyCheckedKeys.erase(it);
				break;
			}
		}
		return true;
	}
	return false;
}
bool InputManager::handleMouseEvent(SDL_Event &ev)
{
	// Most of the time it'll be the mousemotion event
	if (ev.type == SDL_MOUSEMOTION)
	{
		dX = ev.motion.x - x;
		dY = ev.motion.y - y;
		x = ev.motion.x;
		y = ev.motion.y;
	}
	else if (ev.type == SDL_MOUSEWHEEL)
	{
		wheelX = ev.wheel.x;
		wheelY = ev.wheel.y;

	}
	else if (ev.type == SDL_MOUSEBUTTONDOWN)
	{
		buttons[ev.button.button] = true;
	}
	else if (ev.type == SDL_MOUSEBUTTONUP)
	{
		buttons[ev.button.button] = false;
	}
	return true;
}
