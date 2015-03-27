#ifndef BALL_H
#define BALL_H

#include "GameObject.h"
#include "Drawable.h"

class Ball : public GameObject, public Drawable
{
public:
	Ball();
	~Ball();
	void Update() override;
};

#endif