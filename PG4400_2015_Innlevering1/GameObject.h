#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <memory>
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;
	virtual void Draw();
protected:
	std::shared_ptr<SDL_Texture> texture;
	
	// Location and size data
	float x;
	float y;
	int width;
	int height;
};

#endif