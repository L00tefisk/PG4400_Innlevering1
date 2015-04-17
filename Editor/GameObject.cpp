#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
	rect.x = 0;
	rect.y = 0;
	rect.h = 0;
	rect.w = 0;
}

GameObject::~GameObject()
{
	// Intentionally left blank.
}

void GameObject::Draw()
{
	SDL_RenderCopy(renderer, textureList[textureID], NULL, &rect);
}