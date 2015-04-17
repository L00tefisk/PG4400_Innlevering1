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
	
	bool hitTest(SDL_Rect rect2) {
		if(rect.x < rect2.x + rect2.w &&
			rect.x + rect.w > rect2.x &&
			rect.y < rect2.y + rect2.w &&
			rect.h + rect.y > rect2.y) {
			//HIT
			return 1;
		}
		return 0;
	};
protected:
	SDL_Rect rect;
};

#endif