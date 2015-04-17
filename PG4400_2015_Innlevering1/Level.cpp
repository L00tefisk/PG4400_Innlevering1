#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}
void Level::AddBrick(const Brick &b)
{
	map.push_back(b);
}

void Level::RemoveBrick(int x, int y)
{
	for (auto it = map.begin(); it != map.end(); it++)
	{
		SDL_Rect rect = it->getRectangle();

		if (x >= rect.x && x < rect.x + rect.w &&
			y >= rect.y && y < rect.y + rect.h)
		{
			map.erase(it);
			return;
		}
	}
}

void Level::loadLevel()
{
	std::ifstream inputStream("test", std::ifstream::binary | std::ifstream::in);

	if (!inputStream)
		return;

	/*	int numResourcesInUse = 0;
	inputStream >> numResourcesInUse;

	for (int i = 0; i < numResourcesInUse; i++)
	{
	std::string s;
	inputStream >> s;
	resourcesInUse.push_back(s);
	}
	*/
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
		Brick b(rect, textureID);

		AddBrick(b);
	}

	inputStream.close();
}
