#include "Paddle.h"

Paddle::Paddle()
{	
	rect.y = 700;
	rect.x = 100;
	rect.h = 50;
	rect.w = 200;
	loadResource("../Resources/Bats/paddle0002.png");
}
void Paddle::Update(const double& dt)
{
	// Do shit
}
