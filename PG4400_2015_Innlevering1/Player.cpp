#include "Player.h"

Player::Player()
{
	paddle.locationSizeMap.y = 300;
	paddle.locationSizeMap.x = 500;
}

void Player::update()
{
	paddle.locationSizeMap.x = static_cast<float>(InputManager::GetInstance()->getMouseX()) - paddle.locationSizeMap.w/2;

	paddle.Update();
}

Player::~Player()
{
	//TODO
}