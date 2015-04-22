#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"
enum powerType
{
	Grow, Shrink, Slow, Rush, Rocket, Magnet, Super, Split, Kill
};

class PowerUp : public GameObject
{
public:
	PowerUp();
	PowerUp(const powerType &type, const SDL_Rect &rect);

	
	virtual ~PowerUp();
	virtual void Update(const double& dt) override;
	
protected:
	int size;
	float duration;
	powerType type;
};

#endif