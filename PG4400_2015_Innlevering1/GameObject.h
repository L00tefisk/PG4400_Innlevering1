#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = 0;
protected:
	int width; 
	int height;
	float x;
	float y;
};

#endif