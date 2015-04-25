#include "Player.h"

#include "PowerUp.h"

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
	switch (powType)
	{
	case PowerUp::powerType::Shrink:
		if (paddle.rect.w >= 50)
			paddle.rect.w -= 40;
		break;
	case PowerUp::powerType::Grow:
		if (paddle.rect.w <= 300)
			paddle.rect.w += 40;
		break;
	}
}

