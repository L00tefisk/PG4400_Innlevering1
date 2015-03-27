#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
	GameObject(){};
	virtual ~GameObject(){};
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	int width; 
	int height;
	float x;
	float y;
};

#endif