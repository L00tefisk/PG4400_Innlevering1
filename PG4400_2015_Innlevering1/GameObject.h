#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <memory>
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;
protected:
	SDL_Rect locationSizeMap;
};

#endif