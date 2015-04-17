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

	void loadResource(const std::string &path);
	static void Init(SDL_Renderer *renderer);
	static std::vector<std::string> loadedResources;
	unsigned short textureID;

	static void loadAllTextures()
	{
		std::vector<std::string> allTextures;
		allTextures.push_back(std::string("../Resources/Bricks/blue.png"));
		allTextures.push_back(std::string("../Resources/Bricks/red0001.png"));
		allTextures.push_back(std::string("../Resources/Bricks/red0002.png"));
		allTextures.push_back(std::string("../Resources/Bricks/red0003.png"));
		allTextures.push_back(std::string("../Resources/Bricks/unbreakable.png"));

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
	static std::vector<SDL_Texture *> textureList;
	

private:
	
};

#endif