#include "Brick.h"

Brick::Brick()
{
	hp = 1;
}
Brick::Brick(int x, int y, int w, int h, unsigned short type)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	centerX = x + (w / 2);
	centerY = y + (h / 2);
	brickType = type;
	if (brickType == 2)
		hp = 90;
	else 
		hp = 1;
	
}

Brick::~Brick()
{

}

void Brick::DestroyBrick()
{
	hp = 0;
}

bool Brick::Crack()
{
	return --hp == 0;
}

unsigned short Brick::getHP() const
{
	return hp;
}

unsigned short Brick::getBrickType() const
{
	return brickType;
}