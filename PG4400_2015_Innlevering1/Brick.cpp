#include "Brick.h"

Brick::Brick()
{
	hp = 1;
}
Brick::Brick(int x, int y, int w, int h)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}
Brick::Brick(const SDL_Rect& rect)
{
	this->rect = rect;
}
Brick::~Brick()
{

}

void Brick::Update(const double& dt)
{

}
void Brick::Damage() {
	hp--;
	if (hp <= 0)
		delete this;
}