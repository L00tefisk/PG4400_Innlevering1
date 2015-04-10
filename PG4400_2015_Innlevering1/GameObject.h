#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <memory>
#include <string>


class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void Draw();
	virtual void Update() = 0;
protected:
	std::unique<SDL_Renderer*> renderer;
	std::string texPath;
	SDL_Rect locationSizeMap;
};

#endif