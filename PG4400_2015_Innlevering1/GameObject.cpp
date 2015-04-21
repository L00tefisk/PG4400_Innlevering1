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

void GameObject::Draw()
{
	SDL_RenderCopy(renderer, textureList[textureID], NULL, &rect);
}

void GameObject::Update(const double& dt)
{
	// Intentionally left blank.
}

int GameObject::Collide(const GameObject& obj, double dt)
{
	if (rect.x + rect.w > obj.rect.x &&
		rect.y + rect.h > obj.rect.y &&
		rect.x < obj.rect.x + obj.rect.w &&
		rect.y < obj.rect.y + obj.rect.h)
	{
		return true;
	}
	return false;
}

SDL_Rect GameObject::getRectangle() const
{
	return rect;
}