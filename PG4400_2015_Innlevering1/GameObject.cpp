#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	// Intentionally left blank.
}

void GameObject::Draw()
{
	SDL_RenderCopy(renderer, textureList[textureID], NULL, &rect);
}