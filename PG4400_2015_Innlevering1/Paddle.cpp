#include "Paddle.h"

Paddle::Paddle()
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

	leftTextureID = loadResource("../Resources/Bats/paddle1l.png");
	textureID = loadResource("../Resources/Bats/paddle1.png");
	rightTextureID = loadResource("../Resources/Bats/paddle1r.png");
	
}
void Paddle::Draw() {
	SDL_RenderCopy(renderer, textureList[leftTextureID], NULL, &lRect);
	SDL_RenderCopy(renderer, textureList[textureID], NULL, &mRect);
	SDL_RenderCopy(renderer, textureList[rightTextureID], NULL, &rRect);
}

void Paddle::Update(const double& dt)
{
	//mRect.w = rect.w - lRect.w - rRect.w;
	lRect.x = rect.x;
	mRect.x = lRect.x + lRect.w;
	rRect.x = mRect.x + mRect.w;
}