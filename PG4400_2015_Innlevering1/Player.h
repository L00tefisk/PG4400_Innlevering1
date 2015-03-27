#ifndef PLAYER_H
#define PLAYER_H

#include "Paddle.h"

class Player
{
public:
	Player();
	~Player();

	void update();
private:
	Paddle paddle;
};

#endif