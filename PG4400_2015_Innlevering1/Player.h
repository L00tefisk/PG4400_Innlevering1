#ifndef PLAYER_H
#define PLAYER_H

#include "Paddle.h"
#include "InputManager.h"

class Player
{
public:
	Player();
	~Player();

	void update();
private:
	Paddle paddle;
	std::shared_ptr<InputManager> inputManager;
};

#endif