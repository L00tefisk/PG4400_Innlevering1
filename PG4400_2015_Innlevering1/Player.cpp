#include "Player.h"

Player::Player()
{
	paddle.rect.y = 500;
	paddle.rect.x = 500;
	inputManager = InputManager::GetInstance();
}

Player::~Player()
{
	//TODO
}

void Player::Update()
{
	paddle.rect.x = inputManager->getMouseX() - paddle.rect.w/2;

	paddle.Update();
}

void Player::Draw()
{
	paddle.Draw();
}

