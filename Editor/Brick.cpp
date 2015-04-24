#include "Brick.h"

Brick::Brick()
{

	
};

Brick::Brick(const SDL_Rect &rect, unsigned short texID, int type)
{
	this->rect = rect;
	this->textureID = texID;
	this->type = type;
}
Brick::~Brick()
{

}
void Brick::Update()
{

}
bool operator==(const Brick& lhs, const Brick& rhs)
{
	if (&lhs != &rhs)
	{
		if (rhs.rect.x == lhs.rect.x &&
			rhs.rect.y == lhs.rect.y)
			return true;
	}
	return false;
};