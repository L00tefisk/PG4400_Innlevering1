#include "Collider.h";

void Collider::init(const SDL_Rect& rect)
{
	collisionRect = rect;
	colliderList.push_back(collisionRect);
}
