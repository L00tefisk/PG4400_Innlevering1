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
	std::cout << "Drawing." << std::endl;
	std::cout << "Rect (" << rect.x << "," << rect.y << "," << rect.w << "," << rect.h << ")" << std::endl;
	SDL_RenderCopy(renderer, textureList[textureID], NULL, &rect);
}