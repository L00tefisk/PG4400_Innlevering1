#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Brick.h"
#include "Drawable.h"

class Level
{
public:
	Level();
	~Level();
private:
	std::vector<Brick> map;
	int width;
	int height;
};

#endif