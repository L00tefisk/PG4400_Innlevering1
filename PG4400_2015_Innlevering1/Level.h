#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <fstream>
#include "Brick.h"
#include "Drawable.h"

class Level
{
public:
	Level();
	~Level();

	void AddBrick(const Brick &b);
	void RemoveBrick(const Brick &b);
	void loadLevel();
	void draw();
	std::vector<Brick> map;
private:

};

#endif