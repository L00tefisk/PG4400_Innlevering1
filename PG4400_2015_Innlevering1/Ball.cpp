#include "Ball.h"
#include "InputManager.h"

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

	drawList[textureIDList[0]] = rect;

}

/*

*/
int Ball::Collide(const GameObject &obj, double dt)
{
	SDL_Rect tempRect = rect;
	tempRect.x += xSpeed * dt;
	tempRect.y += ySpeed * dt;
	if (tempRect.x + tempRect.w > obj.getRectangle().x &&
		tempRect.y + tempRect.h > obj.getRectangle().y &&
		tempRect.x < obj.getRectangle().x + obj.getRectangle().w &&
		tempRect.y < obj.getRectangle().y + obj.getRectangle().h)
	{
		tempRect.x -= xSpeed * dt;

		if (tempRect.x + tempRect.w > obj.getRectangle().x &&
			tempRect.y + tempRect.h > obj.getRectangle().y &&
			tempRect.x < obj.getRectangle().x + obj.getRectangle().w &&
			tempRect.y < obj.getRectangle().y + obj.getRectangle().h)
			return 1;

		return 2;
	}
	return 0;
}

void Ball::Fire()
{
	if (!onPaddle)
		return;

	onPaddle = false;
	xSpeed = 800;
	ySpeed = -800;
}