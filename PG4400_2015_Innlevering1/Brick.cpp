#include "Brick.h"

Brick::Brick()
{
	hp = 1;
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
	if(hp <= 0)
		Brick::~Brick();
}