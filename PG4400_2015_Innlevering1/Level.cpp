#include <algorithm>

#include "Level.h"

Level::Level()
{
	map = std::shared_ptr<std::vector<Brick>>(new std::vector<Brick>);
}

Level::~Level()
{

}
void Level::AddBrick(const Brick &b)
{
	map->push_back(b);
}

void Level::RemoveBrick(const Brick &b)
{
	SDL_Rect brickRect = b.getRectangle();
	for (auto it = map->begin(); it != map->end(); it++)
	{
		SDL_Rect rect = it->getRectangle();
		if (brickRect.x >= rect.x && brickRect.x < rect.x + rect.w &&
			brickRect.y >= rect.y && brickRect.y < rect.y + rect.h)
		{
			map->erase(it);
			return;
		}
	}
}

void Level::spawnPowerUp(const PowerUp& pow)
{
	pMap.push_back(pow);
}

void Level::loadLevel()
{
	std::ifstream inputStream("test", std::ifstream::binary | std::ifstream::in);
	std::vector<std::string> resourcesInUse;
	if (!inputStream)
		return;

	unsigned int numResourcesInUse;

	inputStream.read(reinterpret_cast<char*>(&numResourcesInUse), sizeof(unsigned int));

	for (unsigned int i = 0; i < numResourcesInUse; i++)
	{
		char buffer[64];

		inputStream.read(buffer, 64);
		resourcesInUse.push_back(buffer);
	}

	inputStream.peek();
	while (!inputStream.eof())
	{

		SDL_Rect rect;
		unsigned short textureID;
		inputStream.read(reinterpret_cast<char*>(&rect), sizeof(SDL_Rect));
		inputStream.read(reinterpret_cast<char*>(&textureID), sizeof(unsigned short));
		inputStream.peek();
		std::cout << "Rect(" << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << ")" << std::endl;
		std::cout << "Texture ID: " << textureID << std::endl;
		Brick b(rect, 0);
		b.loadResource(resourcesInUse[textureID], rect);
		b.centerX = rect.x + (rect.w / 2);
		b.centerY = rect.y + (rect.h / 2);
		AddBrick(b);
	}

	inputStream.close();
};

const std::shared_ptr<std::vector<Brick> > Level::getMap()
{
	return map;
}

bool Level::hasBrick(const SDL_Rect& b)
{

	for (int i = 0; i < map->size(); i++)
		if (map->at(i).getRectangle().x == b.x &&
			map->at(i).getRectangle().y == b.y)
			return true;
	return false;
}


void Level::draw()
{
	for (int i = 0; i < map->size(); i++)
		map->at(i).Draw();

	for (int i = 0; i < pMap.size(); i++)
		pMap[i].Draw();
}
