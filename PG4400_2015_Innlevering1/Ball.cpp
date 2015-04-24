#include "Ball.h"
#include "InputManager.h"

#include "Vector2D.h"

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
	xSpeed = 0;
	ySpeed = 0;
	loadResource("../Resources/Balls/ball0002.png", rect);
	onPaddle = true;
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



void Ball::Fire()
{
	if (!onPaddle)
		return;

	onPaddle = false;
	xSpeed = 200;
	ySpeed = -200;
}
