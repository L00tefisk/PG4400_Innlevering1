#include "Player.h"

Player::Player()
{
	inputManager = InputManager::GetInstance();
}
Player::Player(const SDL_Rect &rect)
{
	
	inputManager = InputManager::GetInstance();
	paddle.rect = rect;
}

Player::~Player()
{
	//TODO
}

void Player::Update()
{
	paddle.rect.x = inputManager->getMouseX();// -paddle.rect.w / 2;

	paddle.Update(0);
}

void Player::Draw()
{
	paddle.Draw();
}

