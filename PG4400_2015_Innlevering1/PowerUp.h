#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

class PowerUp : public GameObject
{
public:
	enum powerType
	{
		Grow, Shrink, Slow, Rush, Rocket, Magnet, Super, Split, Kill
	};

	PowerUp();
	PowerUp(const powerType &type, const SDL_Rect&);

	
	virtual ~PowerUp();
	virtual void Update(const double& dt) override;

	int ypos;

protected:
	int size;
	float duration;
	powerType type;
};

#endif