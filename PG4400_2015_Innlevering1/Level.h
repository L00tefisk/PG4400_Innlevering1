#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <fstream>
#include "Brick.h"
#include "PowerUp.h"

class Level
{
public:
	Level();
	~Level();

	void AddBrick(const Brick &b);
	void RemoveBrick(const Brick &b);
	void spawnPowerUp(const PowerUp &p);
	void loadLevel();
	void draw();

	bool hasBrick(const SDL_Rect &b);

	std::vector<PowerUp> pMap;

	std::vector<Brick> &getMap();
private:
	std::vector<Brick> map;
	
};

#endif