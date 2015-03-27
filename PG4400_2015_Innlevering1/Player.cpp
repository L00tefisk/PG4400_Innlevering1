#include "Player.h"

Player::Player()
{
	paddle.locationSizeMap.y = 20;
}

void Player::update()
{
	paddle.locationSizeMap.x = static_cast<float>(InputManager::GetInstance()->getMouseX());
}