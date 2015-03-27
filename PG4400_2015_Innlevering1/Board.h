#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Brick.h"
#include "Drawable.h"

class Board : public Drawable
{
public:
	Board();
	~Board();
private:
	std::vector<Brick> map;
	int width;
	int height;
};

#endif