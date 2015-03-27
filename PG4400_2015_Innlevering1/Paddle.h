#ifndef PADDLE_H
#define PADDLE_H

#include "GameObject.h"

class Paddle : public GameObject
{
public:
	Paddle();
	void Update();
	void Draw();
private:
};

#endif