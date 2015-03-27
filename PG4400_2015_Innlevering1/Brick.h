#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

class Brick : public GameObject
{
public:
	Brick();
	~Brick();
	void Update() override;
	//void Draw();
};

#endif