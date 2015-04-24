#include "Ball.h"
#include "InputManager.h"

#include "Vector2D.h"
#include "PowerUp.h"

bool Ball::magnet; // How does it work?
bool Ball::speedUp;
bool Ball::speedDown;
bool Ball::superBall;
std::vector<Ball> Ball::balls;
Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::Init()
{
	rect.x = 50;
	rect.y = 100;
	rect.w = 10;
	rect.h = 10;
	centerX = rect.x + (rect.w / 2);
	centerY = rect.y + (rect.h / 2);
	xSpeed = 400;
	ySpeed = -400;
	loadResource("../Resources/Balls/ball0002.png", rect);
}

void Ball::AddBall(bool onPaddle)
{
	Ball b;
	b.Init();
	b.onPaddle = onPaddle;
	balls.push_back(b);
}

void Ball::Update(const double &dt) 
{

	if (onPaddle)
	{
		rect.y = 590;
		rect.x = InputManager::GetInstance()->getMouseX() + 35;
	}
	else
	{
		rect.x += xSpeed * dt;
		rect.y += ySpeed * dt;

		if (rect.x < 0 || rect.x + rect.w > 1280)
			xSpeed *= -1;
		if (rect.y < 0 || rect.y + rect.h > 720)
			ySpeed *= -1;
	}
	centerX = rect.x + (rect.w / 2);
	centerY = rect.y + (rect.h / 2);
	drawList[textureIDList[0]] = rect;

}

void Ball::ApplyPowerUp(int powType)
{
	switch (powType)
	{
	case PowerUp::powerType::Magnet:
		magnet = true;
		break;
	case PowerUp::powerType::Rush:
		speedUp = true;
		break;
	case PowerUp::powerType::Slow:
		speedDown = true;
		break;
	case PowerUp::powerType::Split:
		for (int i = balls.size() * 2; i > 0; i--)
			AddBall(false);
		break;
	case PowerUp::powerType::Super:
		superBall = true;
		break;
	}
}

void Ball::Fire()
{
	if (!onPaddle)
		return;

	onPaddle = false;
	xSpeed = 400;
	ySpeed = -400;
}

