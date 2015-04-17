#ifndef EDITOR_H
#define EDITOR_H

#include <fstream>
#include "Brick.h"

class Editor
{
public:
	static Editor *GetInstance()
	{
		if (instance == NULL)
			instance = new Editor();
		
		return instance;
	}
	void AddBrick(const Brick &b)
	{
		map.push_back(b);
		for (int i = 0; i < resourcesInUse.size(); i++)
		{
			if (resourcesInUse[i] == Drawable::loadedResources[b.textureID])
				return;
		}
		resourcesInUse.push_back(Drawable::loadedResources[b.textureID]);
		std::cout << "Added brick at (" << b.rect.x << "," << b.rect.y << ")" << std::endl;
	}
	void RemoveBrick(int x, int y)
	{
		for (auto it = map.begin(); it != map.end(); it++)
		{
			if (x >= it->rect.x && x < it->rect.x + it->rect.w &&
				y >= it->rect.y && y < it->rect.y + it->rect.h)
			{
				map.erase(it);
				return;
			}
		}
	}

	void SaveLevel()
	{
		std::ofstream outputStream("test", std::ofstream::out | std::ofstream::trunc);

		outputStream << resourcesInUse.size() << std::endl;
		for (int i = 0; i < resourcesInUse.size(); i++)
		{
			outputStream << resourcesInUse[i] << std::endl;
		}
		
		outputStream.close();
		outputStream.open("test", std::ifstream::binary | std::ifstream::app);

		for (Brick b : map)
		{
			outputStream << b.rect.x << std::endl;
			outputStream << b.rect.y << std::endl;
			outputStream << b.rect.w << std::endl;
			outputStream << b.rect.h << std::endl;
			for (int i = 0; i < resourcesInUse.size(); i++)
			{
				if (Drawable::loadedResources[b.textureID] == resourcesInUse[i])
				{
					outputStream << i << std::endl;
					break;
				}
			}
		}
	}

	void loadLevel()
	{
		std::ifstream inputStream("test", std::ifstream::in);
		if (!inputStream)
			return;
		int numResourcesInUse;
		inputStream >> numResourcesInUse;
		for (int i = 0; i < numResourcesInUse; i++)
		{
			std::string s;
			inputStream >> s;
			resourcesInUse.push_back(s);
		}
		inputStream.close();
		inputStream.open("test", std::ifstream::binary | std::ifstream::app);

		while (!inputStream.eof())
		{
			Brick b;
			inputStream >> b.rect.x;
			inputStream >> b.rect.y;
			inputStream >> b.rect.w;
			inputStream >> b.rect.h;
			inputStream >> b.textureID;
		}

		inputStream.close();
	}

	void draw()
	{
		for (Brick b : map)
			b.Draw();
	}

	void changeBrickID(bool direction)
	{
		if (direction)
			currentBrickID++;
		else
			currentBrickID--;
		
		if (currentBrickID > Drawable::loadedResources.size() - 1)
			currentBrickID = 0;
		else if (currentBrickID < 0)
			currentBrickID = Drawable::loadedResources.size() - 1;
	}
	int currentBrickID;
	std::vector<std::string> resourcesInUse;
	std::string levelName;
	std::vector<Brick> map;


private:
	static std::vector<SDL_Texture *> textureList;
	static Editor* instance;
};

Editor *Editor::instance = NULL;
#endif