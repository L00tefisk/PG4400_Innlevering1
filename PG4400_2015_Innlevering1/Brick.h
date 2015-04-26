#ifndef BRICK_H
#define BRICK_H

#include <map>

#include "GameObject.h"
#include "Drawable.h"


class Brick : public GameObject
{
public:
	Brick();
	Brick(int x, int y, int w, int h, unsigned short type);
	Brick(const SDL_Rect &rect, unsigned short type);

	virtual ~Brick();
	bool Crack();

private:
	unsigned short hp;
	unsigned short brickType;
};

#endif