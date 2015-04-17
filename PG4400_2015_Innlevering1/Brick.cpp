#include "Brick.h"

Brick::Brick()
{

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
