#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = 0;
protected:
	float x;
	float y;
};

#endif