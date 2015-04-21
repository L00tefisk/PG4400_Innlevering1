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