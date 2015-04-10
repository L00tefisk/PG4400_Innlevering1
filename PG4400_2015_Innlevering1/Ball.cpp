#include "Ball.h"

Ball::Ball()
{
	
}

Ball::~Ball()
{

}

int hitTest (SDL_Rect rect1, SDL_Rect rect2)
{
	if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.w &&
		rect1.h + rect1.y > rect2.y)
	{
		//HIT
	}
}

void Ball::Update()
{
	rect.x += xSpeed;
	rect.y += ySpeed;
	
	if (rect.x < 0 || rect.x + rect.w > 800)
		xSpeed *= -1;
	if (rect.y < 0 || rect.y + rect.y > 600)
		ySpeed *= -1;
}
