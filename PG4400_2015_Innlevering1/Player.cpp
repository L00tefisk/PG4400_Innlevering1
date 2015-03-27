#include "Player.h"

Player::Player()
{
	paddle.y = 20;
}

void Player::update()
{
	paddle.x = static_cast<float>(InputManager::GetInstance()->getMouseX());
}