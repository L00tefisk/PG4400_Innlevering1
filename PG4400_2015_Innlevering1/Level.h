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
	void loadLevel(std::string level);
	void changeLevel(std::string level);
	void draw();

	bool hasBrick(const SDL_Rect &b);
	bool isDone();

	std::vector<PowerUp> pMap;
	std::vector<Brick> &getMap();

protected:
	std::vector<Brick> map;

private:
	unsigned short indestructibleBricksCount;
	GameObject background;

	
};

#endif