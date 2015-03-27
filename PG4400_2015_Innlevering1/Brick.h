#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

class Brick : public GameObject
{
public:
	Brick();
	~Brick();
	void Update();
	void Draw();
};

#endif