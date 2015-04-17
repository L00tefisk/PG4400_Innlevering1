#ifndef COLLIDER_H
#define COLLIDER_H

#include <array>

#include "SDL.h"
#include <vector>

class Collider
{
public:
	void init(const SDL_Rect&);
	virtual void onHit() = 0;
	
protected:
	static std::vector<SDL_Rect> colliderList;
	SDL_Rect& collisionRect;
};

#endif