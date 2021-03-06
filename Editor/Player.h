#ifndef PLAYER_H
#define PLAYER_H

#include "Paddle.h"
#include "InputManager.h"

class Player
{
public:
	Player(const SDL_Rect &rect);
	~Player();

	void Update();
	void Draw();

	Paddle paddle;
private:
	std::shared_ptr<InputManager> inputManager;
};

#endif