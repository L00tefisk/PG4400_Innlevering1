#include "Ball.h"

Ball::Ball () {
	rect.x = 500;
	rect.y = 500;
	rect.w = 25;
	rect.h = 25;
	xSpeed = 1;
	ySpeed = xSpeed;
	loadResource ("../Resources/Balls/ball0001.png");
}

Ball::~Ball () {

}

int hitTest (SDL_Rect rect1, SDL_Rect rect2) {
	if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.w &&
		rect1.h + rect1.y > rect2.y) {
		//HIT
		return 1;
	}
	return 0;
}

void Ball::Update (const double &dt) {
	rect.x += xSpeed * dt;
	rect.y -= ySpeed * dt;

	if (rect.x < 0 || rect.x + rect.w > 1280)
		xSpeed *= -1;
	if (rect.y < 0 || rect.y + rect.h > 720)
		ySpeed *= -1;
}
