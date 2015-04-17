#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <memory>
#include <string>

#include "Drawable.h"

class GameObject : public Drawable
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void Update(const double& dt) = 0;
	virtual void Draw();

	SDL_Rect getRectangle();
	
protected:
	SDL_Rect rect;
};

#endif