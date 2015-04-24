#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
	// Intentionally left blank.
}

GameObject::~GameObject()
{
	// Intentionally left blank.
}

void GameObject::Init()
{
	// Intentionally left blank.
}
void GameObject::Draw()
{
	for (int i = 0; i < textureIDList.size(); i++)
		SDL_RenderCopy(renderer, textureList[textureIDList[i]], NULL, &drawList[textureIDList[i]]);
}

void GameObject::Update(const double& dt)
{
	// Intentionally left blank.
}

Vector2D GameObject::Collide(const GameObject& obj, double dt)
{
	// Very simplified SAT collision detection for rectangle vs rectangle collision.
	SDL_Rect objRect = obj.getRectangle();
	float overlapX1 = 90000;
	float overlapX2 = 90000;
	float overlapY1 = 90000;
	float overlapY2 = 90000;

	float minX = 0;
	float minY = 0;

	overlapX1 = objRect.x + objRect.w - rect.x;
	overlapX2 = objRect.x - (rect.x + rect.w);

	overlapY1 = objRect.y + objRect.h - rect.y;
	overlapY2 = objRect.y - (rect.y + rect.h);

	//If there is an overlap then X1, Y1 will always be positive and X2, Y2 will always be negative

	if (overlapX1 < 0 || overlapX2 >= 0 ||
		overlapY1 < 0 || overlapY2 >= 0)
		return Vector2D(0, 0);

	// Return smallest x and y overlap.
	if (abs(overlapX1) < abs(overlapX2))
		minX = overlapX1;
	else
		minX = overlapX2;

	if (abs(overlapY1) < abs(overlapY2))
		minY = overlapY1;
	else
		minY = overlapY2;


	return Vector2D(minX, minY);
}

const SDL_Rect& GameObject::getRectangle() const
{
	return rect;
}

void GameObject::setRectangle(const SDL_Rect& rect)
{
	this->rect = rect;
}