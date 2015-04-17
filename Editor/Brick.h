#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"
#include "Drawable.h"

class Brick : public GameObject
{
public:
	Brick();
	Brick(const SDL_Rect &rect, const unsigned short texID);
	~Brick();
	void Update() override;
};

#endif