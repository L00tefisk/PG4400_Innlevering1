#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

class PowerUp : public GameObject
{
public:
	PowerUp();
	virtual ~PowerUp() = 0;
protected:
	const float fallSpeed = 1;

};

#endif