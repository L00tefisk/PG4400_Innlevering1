#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <memory>
#include <string>

#include "Drawable.h"
#include "Vector2D.h"

class GameObject : public Drawable
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void Init();
	virtual void Update(const double& dt);
	virtual void Draw();
	virtual Vector2D Collide(const GameObject &obj, double dt);

	const SDL_Rect& getRectangle() const;
	void setRectangle(const SDL_Rect& rect);
	float centerX;
	float centerY;
protected:
	SDL_Rect rect;

};

#endif