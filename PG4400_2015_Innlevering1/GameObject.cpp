#include "GameObject.h"
#include "DrawEngine.h"
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
	int success = DrawEngine::GetInstance().Draw(locationSizeMap, texPath);
}

