#ifndef PLAYER_H
#define PLAYER_H

#include "Paddle.h"
#include "InputManager.h"

class Player
{
public:
	Player();
	~Player();

	void Update();
	void Draw();
private:
	Paddle paddle;
	std::shared_ptr<InputManager> inputManager;
};

#endif