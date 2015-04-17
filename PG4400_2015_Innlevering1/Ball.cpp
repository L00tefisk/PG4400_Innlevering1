#include "Ball.h"

Ball::Ball () {
	rect.x = 500;
	rect.y = 500;
	rect.w = 25;
	rect.h = 25;
	xSpeed = 0.3;
	ySpeed = xSpeed;
	textureID = loadResource ("../Resources/Balls/ball0001.png");
}

Ball::~Ball () {

}



void Ball::Update (const double &dt) {
	rect.x += xSpeed * dt;
	rect.y -= ySpeed * dt;

	if (rect.x < 0 || rect.x + rect.w > 1280)
		xSpeed *= -1;
	if ((rect.y < 0 || rect.y + rect.h > 720))
		ySpeed *= -1;
}
