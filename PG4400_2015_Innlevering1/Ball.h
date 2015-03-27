#ifndef BALL_H
#define BALL_H

#include "GameObject.h"

class Ball : public GameObject
{
public:
	Ball();
	~Ball();
	void Update();
	void Draw();
};

#endif