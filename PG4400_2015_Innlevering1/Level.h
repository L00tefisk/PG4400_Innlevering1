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

	//void LoadLevel();
private:
	std::vector<GameObject> map;
	int width;
	int height;
};

#endif