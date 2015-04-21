#ifndef PLAYER_H
#define PLAYER_H

#include "Paddle.h"
#include "InputManager.h"

class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();

	Paddle paddle;
private:
	std::shared_ptr<InputManager> inputManager;
};

#endif