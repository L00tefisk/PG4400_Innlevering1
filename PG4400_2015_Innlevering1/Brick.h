#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"
#include "Drawable.h"

class Brick : public GameObject
{
public:
	Brick();
	~Brick();
	virtual void Update(const double& dt) override;
};

#endif