#include "Player.h"

#include "PowerUp.h"
#include "Ball.h"

Player::Player()
{
	
}
Player::~Player()
{
	//TODO
}

void Player::Init()
{

	inputManager = InputManager::GetInstance();
	rect.x = 0;
	rect.y = 720 - 50;
	rect.w = 150;
	rect.h = rect.w / 4;

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
	lives = 3;
}
void Player::Update(const double& dt)
{
	rect.x = inputManager->getMouseX() - (rect.w / 2); // -paddle.rect.w / 2;

	mRect.w = rect.w - lRect.w - rRect.w;

	lRect.x = rect.x;
	mRect.x = lRect.x + lRect.w;
	rRect.x = mRect.x + mRect.w;
	drawList[textureIDList[0]] = lRect;
	drawList[textureIDList[1]] = mRect;
	drawList[textureIDList[2]] = rRect;
}

void Player::ApplyPowerUp(int powType)
{
	int shrinksize = 40;
	switch (powType)
	{
	case PowerUp::powerType::Shrink:
		if(rect.w > 150 - (shrinksize * 2))
			rect.w -= shrinksize;
		break;
	case PowerUp::powerType::Grow:
		if(rect.w < 150 + shrinksize * 2)
			rect.w += shrinksize;
		break;
	case PowerUp::powerType::Kill:
		lives--;
		GameManager::balls.clear();
		Ball::AddBall(true);
		break;
	case PowerUp::powerType::Slow:
		Ball::ApplyPowerUp(powType);
		break;
	case PowerUp::powerType::Rush:
		Ball::ApplyPowerUp(powType);
		break;
	case PowerUp::powerType::Magnet:
		Ball::ApplyPowerUp(powType);
		break;
	case PowerUp::powerType::Split:
		Ball::ApplyPowerUp(powType);
		break;

	}
}

