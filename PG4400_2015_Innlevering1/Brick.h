#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"
#include "Drawable.h"

class Brick : public GameObject
{
public:
	Brick();
	Brick(int x, int y, int w, int h);
	Brick(const SDL_Rect &rect);

	void Damage();
	virtual ~Brick();
	virtual void Update(const double& dt) override;
private:
	int hp;
};

#endif