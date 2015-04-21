#ifndef PADDLE_H
#define PADDLE_H

#include "GameObject.h"
#include "Drawable.h"

class Paddle : public GameObject
{
	friend class Player;
public:
	Paddle();
	virtual void Init() override;
	virtual void Update(const double& dt);

private:
	int leftTextureID;
	int rightTextureID;
	SDL_Rect lRect;
	SDL_Rect mRect;
	SDL_Rect rRect;
};

#endif