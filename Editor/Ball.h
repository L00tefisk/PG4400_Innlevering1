#ifndef BALL_H
#define BALL_H

#include "GameObject.h"

class Ball : public GameObject
{
public:
	Ball();
	~Ball();

	void Update() override;
	void ApplyPowerUp(int powerUp);
private:
	// Powerup flags
	static bool magnet; // How does it work?
	static bool speedUp;
	static bool speedDown;

	float xSpeed;
	float ySpeed;
};

#endif