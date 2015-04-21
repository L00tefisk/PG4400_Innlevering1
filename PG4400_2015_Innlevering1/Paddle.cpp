#include "Paddle.h"

Paddle::Paddle()
{	

}
void Paddle::Init()
{
	rect.x = 100;
	rect.y = 600;
	rect.w = 100;
	rect.h = 25;

	lRect.h = rect.h;
	mRect.h = rect.h;
	rRect.h = rect.h;

	lRect.y = rect.y;
	mRect.y = rect.y;
	rRect.y = rect.y;

	rRect.w = rect.h * 1.5;
	lRect.w = rect.h / 2;
	mRect.w = rect.w - lRect.w - rRect.w;

	loadResource("../Resources/Bats/paddle1l.png", lRect);
	loadResource("../Resources/Bats/paddle1.png", mRect);
	loadResource("../Resources/Bats/paddle1r.png", rRect);

}


void Paddle::Update(const double& dt)
{
	//mRect.w = rect.w - lRect.w - rRect.w;
	lRect.x = rect.x;
	mRect.x = lRect.x + lRect.w;
	rRect.x = mRect.x + mRect.w;

	drawList[textureIDList[0]] = lRect;
	drawList[textureIDList[1]] = mRect;
	drawList[textureIDList[2]] = rRect;
}