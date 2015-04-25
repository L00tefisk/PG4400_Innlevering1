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
	hp = 0;
}
Brick::Brick(const SDL_Rect& rect, unsigned short type) : 
Brick(rect.x, rect.y, rect.w, rect.h, type)
{

}
Brick::~Brick()
{

}



bool Brick::Crack()
{
	if (brickType != 2)
	{

		return --hp == 0;
	}

	return false;
}

