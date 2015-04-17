#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <fstream>
#include "Brick.h"
#include "Drawable.h"

class Level
{
public:
	Level(){};
	~Level(){};

	void AddBrick(const Brick &b);
	void RemoveBrick(const int x, const int y);
	void loadLevel();

private:
	std::vector<Brick> map;
};

#endif