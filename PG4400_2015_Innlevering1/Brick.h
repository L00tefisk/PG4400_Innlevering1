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

	virtual ~Brick();
	bool Crack();
	void DestroyBrick();
	unsigned short getHP() const;
	unsigned short getBrickType() const;
private:
	unsigned short hp;
	unsigned short brickType;
};

#endif