#include "Brick.h"

Brick::Brick()
{
	hp = 1;
}

Brick::Brick(const SDL_Rect &rect, const unsigned short texID)
{
	this->rect = rect;
	this->textureID = texID;
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