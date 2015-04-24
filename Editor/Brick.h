#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"
#include "Drawable.h"

class Brick : public GameObject
{
public:
	Brick();
	Brick(const SDL_Rect &rect, unsigned short texID, int type);
	~Brick();
	
	void Update() override;
	short type;
};

bool operator==(const Brick& lhs, const Brick& rhs);

#endif