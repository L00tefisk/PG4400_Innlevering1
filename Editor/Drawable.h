#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <memory>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>


class Drawable
{
public:
	Drawable();
	virtual ~Drawable();
	virtual void Draw() = 0;

	virtual void loadResource(const std::string &path);
	static void Init(SDL_Renderer *renderer);
	static std::vector<std::string> loadedResources;
	unsigned short textureID;
	static std::vector<SDL_Texture *> textureList;

	static void loadAllTextures()
	{
		std::vector<std::string> allTextures;
		allTextures.push_back(std::string("../Resources/Bricks/blue.png"));			//ID = 0;
		allTextures.push_back(std::string("../Resources/Bricks/purple.png"));		//ID = 1;
		allTextures.push_back(std::string("../Resources/Bricks/pink.png"));			//ID = 2;
		allTextures.push_back(std::string("../Resources/Bricks/ice.png"));			//ID = 3;
		allTextures.push_back(std::string("../Resources/Bricks/green.png"));		//ID = 4;
		allTextures.push_back(std::string("../Resources/Bricks/yellow.png"));		//ID = 5;
		allTextures.push_back(std::string("../Resources/Bricks/red0001.png"));		//ID = 6;
		allTextures.push_back(std::string("../Resources/Bricks/red0002.png"));		//ID = 7;
		allTextures.push_back(std::string("../Resources/Bricks/red0003.png"));		//ID = 8;
		allTextures.push_back(std::string("../Resources/Bricks/unbreakable.png"));	//ID = 9;

		for (int i = 0; i < allTextures.size(); i++)
		{
			SDL_Surface *surface = IMG_Load(allTextures[i].c_str());
			if (surface == NULL)
				std::cout << "Load failed: " << SDL_GetError() << std::endl;

			SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

			if (texture == NULL)
				std::cout << "Texture creation failed." << SDL_GetError() << std::endl;
			// and store them in textureArray
			textureList.push_back(texture);
			loadedResources.push_back(allTextures[i]);
		}
	}

protected:
	static SDL_Renderer *renderer;
	
	

private:
	
};

#endif