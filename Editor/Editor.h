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

	void AddBrick(const Brick& b)
	{
		for (const Brick& brick : map) {
			if(brick == b) {
				RemoveBrick(brick.rect.x, brick.rect.y);
			}
		}
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

		unsigned int numResourcesInUse = resourcesInUse.size();
		outputStream.write(reinterpret_cast<char*>(&numResourcesInUse), sizeof(unsigned int));
		
		for (std::string s : resourcesInUse)
		{
			outputStream.write(s.c_str(), 64);
		}


		short w = map[0].rect.w;
		short h = map[0].rect.h;
		short x = 0;
		short y = 0;
		short type = 0;
		outputStream.write(reinterpret_cast<char*>(&w), sizeof(short));
		outputStream.write(reinterpret_cast<char*>(&h), sizeof(short));
		for (int i = 0; i < map.size(); i++)
		{
		
			x = map[i].rect.x;
			y = map[i].rect.y;
			type = map[i].type;
			outputStream.write(reinterpret_cast<char*>(&x), sizeof(short));
			outputStream.write(reinterpret_cast<char*>(&y), sizeof(short));
			outputStream.write(reinterpret_cast<char*>(&type), sizeof(short));


			for (unsigned short j = 0; j < resourcesInUse.size(); j++)
			{
				if (Drawable::loadedResources[map[i].textureID] == resourcesInUse[j])
				{
					outputStream.write(reinterpret_cast<char*>(&j), sizeof(unsigned short));
					break;
				}
			}
		}

		outputStream.close();
	}

	void loadLevel()
	{
		short x, y, w, h;
		unsigned short textureID;
		SDL_Rect rect;
		short type; 
		std::ifstream inputStream("test", std::ifstream::binary | std::ifstream::in);
		
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



		inputStream.read(reinterpret_cast<char*>(&w), sizeof(short));
		inputStream.read(reinterpret_cast<char*>(&h), sizeof(short));
		while (!inputStream.eof())
		{
			

			inputStream.read(reinterpret_cast<char*>(&x), sizeof(short));
			inputStream.read(reinterpret_cast<char*>(&y), sizeof(short));
			inputStream.read(reinterpret_cast<char*>(&type), sizeof(short));

			inputStream.read(reinterpret_cast<char*>(&textureID), sizeof(unsigned short));
			inputStream.peek();

			std::cout << "Rect(" << x << ", " << y << ", " << w << ", " << h << ")" << std::endl;
			std::cout << "Texture ID: " << textureID << std::endl;

			
			rect.x = x;
			rect.y = y;
			rect.w = w;
			rect.h = h;
			Brick b(rect, textureID, type);

			b.loadResource(resourcesInUse[textureID]);

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