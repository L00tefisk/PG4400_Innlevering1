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

	bool hasBrick(const SDL_Rect &b);
	const std::shared_ptr< std::vector<Brick> > getMap();
private:
	std::shared_ptr< std::vector<Brick> > map;

};

#endif