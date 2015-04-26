#ifndef BALL_H
#define BALL_H

#include "GameObject.h"
#include "Vector2D.h"
#include "GameManager.h"

class Ball : public GameObject
{
public:
	virtual ~Ball();

	virtual void Init() override;
	virtual void Update(const double& dt) override;
	virtual void Fire();
	virtual void ResolveCollision(Vector2D& overlapVector);

	static void AddBall(bool onPaddle);
	static void ApplyPowerUp(int powType);

	float ySpeed;
	float xSpeed;
	static bool magnet; // How does it work?
	static bool speedUp;
	static bool speedDown;
	static bool superBall;

	bool onPaddle;
	float relativeHitPositionX;
private:
	Ball();
	
	
	static std::vector<Ball>& balls;

	// Powerup flags
	

};

#endif