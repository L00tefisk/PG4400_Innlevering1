#ifndef PADDLE_H
#define PADDLE_H

#include "GameObject.h"
#include "Drawable.h"

class Paddle : public GameObject
{
	friend class Player;

public:
	Paddle();
	void Update() override;
	void Draw();
	
	

};

#endif