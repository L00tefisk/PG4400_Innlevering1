#include "Player.h"

Player::Player()
{
	paddle.locationSizeMap.y = 500;
	paddle.locationSizeMap.x = 500;
	inputManager = InputManager::GetInstance();
}

Player::~Player()
{
	//TODO
}

void Player::update()
{
	paddle.locationSizeMap.x = inputManager->getMouseX() - paddle.locationSizeMap.w/2;

	paddle.Update();
}

