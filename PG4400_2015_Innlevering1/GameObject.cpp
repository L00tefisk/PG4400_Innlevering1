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

SDL_Rect GameObject::getRectangle()
{
	return rect;
}