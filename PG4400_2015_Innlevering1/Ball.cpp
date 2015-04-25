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
	rect.x = 200;
	rect.y = 200;
	rect.w = 25;
	rect.h = 25;
	centerX = rect.x + (rect.w / 2);
	centerY = rect.y + (rect.h / 2);
	xSpeed = rand() % 800 - 400;
	ySpeed = rand() % 800 - 400;
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
		rect.y = 720 - 50 - rect.h;
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
	int size = balls.size();
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
		for (int i = 0; i < size && balls.size() < 100; i++)
		{
			AddBall(false);
			balls[balls.size() - 1].rect = balls[i].rect;
			if (balls[i].xSpeed < balls[i].ySpeed)
			{
				balls[balls.size() - 1].xSpeed = -balls[i].xSpeed;
				balls[balls.size() - 1].ySpeed = balls[i].ySpeed;
			}
			else
			{
				balls[balls.size() - 1].xSpeed = balls[i].xSpeed;
				balls[balls.size() - 1].ySpeed = -balls[i].ySpeed;
			}
		}
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

