#include "Player.h"

#include "PowerUp.h"
#include "Ball.h"

Player::Player()
{
	inputManager = InputManager::GetInstance();
}
Player::~Player()
{
	//TODO
}

void Player::Init()
{
	paddle.Init();
}
void Player::Update()
{
	paddle.rect.x = inputManager->getMouseX() - (paddle.rect.w / 2);;// -paddle.rect.w / 2;

	paddle.Update(0);
}

void Player::Draw()
{
	paddle.Draw();
}

void Player::ApplyPowerUp(int powType)
{
	int shrinksize = 40;
	switch (powType)
	{
	case PowerUp::powerType::Shrink:
		if(paddle.rect.w > 150 - (shrinksize * 2))
			paddle.rect.w -= shrinksize;
		break;
	case PowerUp::powerType::Grow:
		if(paddle.rect.w < 150 + shrinksize * 2)
			paddle.rect.w += shrinksize;
		break;
	case PowerUp::powerType::Kill:
		//TODO
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

