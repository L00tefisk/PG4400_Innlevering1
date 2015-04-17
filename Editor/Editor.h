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
		std::cout << "Added brick at (" << b.rect.x << "," << b.rect.y << ")" << std::endl;
		map.push_back(b);
		for (int i = 0; i < resourcesInUse.size(); i++)
		{
			if (resourcesInUse[i] == Drawable::loadedResources[b.textureID])
				return;
		}
		resourcesInUse.push_back(Drawable::loadedResources[b.textureID]);
		
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
		std::ofstream outputStream("test", std::ofstream::binary | std::ofstream::out | std::ofstream::trunc);

		//int size = resourcesInUse.size();
		//outputStream << size << std::endl;

		//for (int i = 0; i < resourcesInUse.size(); i++)
		//{
		//	outputStream << resourcesInUse[i] << std::endl;
		//}
		//outputStream.clear();
		for (int i = 0; i < map.size(); i++)
		{
		
			outputStream.write(reinterpret_cast<char*>(&map[i].rect), sizeof(SDL_Rect));

			for (unsigned short i = 0; i < resourcesInUse.size(); i++)
			{
				if (Drawable::loadedResources[map[i].textureID] == resourcesInUse[i])
				{
					outputStream.write(reinterpret_cast<char*>(&i), sizeof(unsigned short));
					break;
				}
			}
		}
		outputStream.close();
	}

	void loadLevel()
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
			Brick b;
			b.rect = rect;
			b.textureID = textureID;
			AddBrick(b);
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