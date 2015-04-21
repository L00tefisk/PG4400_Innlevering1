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
	virtual void Update(const double& dt);
	virtual void Draw();
	virtual int Collide(const GameObject &obj, double dt);

	SDL_Rect getRectangle() const;
	float centerX;
	float centerY;
protected:
	SDL_Rect rect;

};

#endif