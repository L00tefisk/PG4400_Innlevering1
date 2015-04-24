#ifndef BALL_H
#define BALL_H

#include "GameObject.h"
#include "Vector2D.h"
class Ball : public GameObject
{
public:
	Ball();
	~Ball();
	virtual void Init() override;
	virtual void Update(const double& dt) override;
	virtual void Fire();

	float ySpeed;
	float xSpeed;
private:
	
	bool onPaddle;
};

#endif