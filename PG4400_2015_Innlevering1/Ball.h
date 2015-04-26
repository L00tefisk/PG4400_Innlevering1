#ifndef BALL_H
#define BALL_H


#include "GameManager.h"

class Ball : public GameObject
{
public:
	virtual ~Ball();

	virtual void Init() override;
	virtual void Update(const double dt) override;
	virtual void Fire();
	virtual void ResolveCollision(Vector2D& overlapVector);
	
	static void Reset();
	static void AddBall(bool onPaddle);
	static void ApplyPowerUp(int powType);

	float ySpeed;
	float xSpeed;

	// Powerup flags
	static bool powMagnet; // How does it work?
	static bool powSpeedUp;
	static bool powSpeedDown;
	static bool powSuperBall;

	bool onPaddle;
	int relativeHitPositionX;
private:
	Ball();


	static std::vector<Ball>& balls;

	// Powerup flags
};

#endif