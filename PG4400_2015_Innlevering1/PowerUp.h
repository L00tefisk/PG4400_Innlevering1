#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

class PowerUp : public GameObject
{
public:
	enum powerType
	{
		Grow,
		Magnet, 
		Super, 
		Split,
		Kill, 
		Slow, 
		Shrink, 
		Rush
	};

	PowerUp();
	PowerUp(const powerType &type, const SDL_Rect&);

	virtual ~PowerUp();
	virtual void Update(const double dt) override;
	powerType type;

protected:
	int size;
	float duration;
};

#endif