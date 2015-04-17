#include "Player.h"

Player::Player(const SDL_Rect &rect)
{
	paddle.rect = rect;
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

