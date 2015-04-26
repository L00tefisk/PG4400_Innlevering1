#ifndef PLAYER_H
#define PLAYER_H

#include "InputManager.h"
#include "GameObject.h"

class Player : public GameObject
{
	friend class Ball;
public:
	Player();
	~Player();

	void Init() override;
	void Update(const double& dt) override;
	void ApplyPowerUp(int powType);

	int lives;
private:
	int leftTextureID;
	int rightTextureID;
	SDL_Rect lRect;
	SDL_Rect mRect;
	SDL_Rect rRect;

	std::shared_ptr<InputManager> inputManager;
};

#endif