#ifndef BALL_H
#define BALL_H

#include "GameObject.h"
#include "Vector2D.h"

class Ball : public GameObject
{
public:
	virtual ~Ball();

	virtual void Init() override;
	virtual void Update(const double& dt) override;
	virtual void Fire();

	static void AddBall(bool onPaddle);
	static void ApplyPowerUp(int powType);

	float ySpeed;
	float xSpeed;
	static std::vector<Ball> balls;
private:
	Ball();
	// Powerup flags
	static bool magnet; // How does it work?
	static bool speedUp;
	static bool speedDown;
	static bool superBall;
	bool onPaddle;
};

#endif