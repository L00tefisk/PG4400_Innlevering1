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
	virtual void Update(const double dt);
	virtual void Draw() override;
	virtual Vector2D Collide(const GameObject &obj);
	

	const SDL_Rect& getRectangle() const;
	Vector2D getCenter() const;
	void setRectangle(const SDL_Rect& rect);

protected:
	SDL_Rect rect;
	float centerX;
	float centerY;

};

#endif