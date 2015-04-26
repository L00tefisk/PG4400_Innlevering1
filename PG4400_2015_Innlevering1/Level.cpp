#include <algorithm>

#include "Level.h"
#include "GameManager.h"
Level::Level()
{
	indestructibleBricksCount = 0;
	background.loadResource("../Resources/Background/background0008.png", GameManager::GetWindowRectangle());
}

Level::~Level()
{

}
void Level::AddBrick(const Brick &b)
{
	map.push_back(b);
}

void Level::RemoveBrick(const Brick &b)
{
	SDL_Rect brickRect = b.getRectangle();
	for (auto it = map.begin(); it != map.end(); it++)
	{
		SDL_Rect rect = it->getRectangle();
		if (brickRect.x >= rect.x && brickRect.x < rect.x + rect.w &&
			brickRect.y >= rect.y && brickRect.y < rect.y + rect.h)
		{
			map.erase(it);
			return;
		}
	}
}

void Level::loadLevel(std::string level)
{
	short x, y, w, h;
	unsigned short textureID;
	unsigned short type;
	unsigned int numResourcesInUse;

	SDL_Rect rect;
	std::ifstream inputStream;
	inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::vector<std::string> resourcesInUse;
	try{
		inputStream.open(level.c_str(), std::ifstream::binary | std::ifstream::in);



		inputStream.read(reinterpret_cast<char*>(&numResourcesInUse), sizeof(unsigned int));

		for (unsigned int i = 0; i < numResourcesInUse; i++)
		{
			char buffer[64];

			inputStream.read(buffer, 64);
			resourcesInUse.push_back(buffer);
		}

		std::cout << numResourcesInUse << " resources loaded" << std::endl;
		inputStream.peek();


		inputStream.read(reinterpret_cast<char*>(&w), sizeof(short));
		inputStream.read(reinterpret_cast<char*>(&h), sizeof(short));
		while (!inputStream.eof())
		{

			inputStream.read(reinterpret_cast<char*>(&x), sizeof(short));
			inputStream.read(reinterpret_cast<char*>(&y), sizeof(short));
			inputStream.read(reinterpret_cast<char*>(&type), sizeof(short));
			inputStream.read(reinterpret_cast<char*>(&textureID), sizeof(unsigned short));
			inputStream.peek();

			if (type == 2)
				indestructibleBricksCount++;

			rect.x = x;
			rect.y = y;
			rect.w = w;
			rect.h = h;
			Brick b(rect.x, rect.y, rect.w, rect.h, type);
			b.loadResource(resourcesInUse[textureID], rect);

			AddBrick(b);
		}

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "failed to open or read file: " << e.what() << std::endl;
	}

	inputStream.close();
};
std::vector<Brick> &Level::getMap()
{
	return map;
}

bool Level::hasBrick(const SDL_Rect& b)
{
	SDL_Rect tempRect;
	for (unsigned int i = 0; i < map.size(); i++)
	{
		tempRect = map.at(i).getRectangle();
		if (b.x > tempRect.x + tempRect.w ||
			b.y > tempRect.y + tempRect.h ||
			tempRect.x > b.x + b.w ||
			tempRect.y > b.y + b.h)
			return false;
	}
	return false;
}


void Level::draw()
{
	background.Draw();
	for (unsigned int i = 0; i < map.size(); i++)
		map.at(i).Draw();

}

bool Level::isDone()
{
	return map.size() == indestructibleBricksCount;
}