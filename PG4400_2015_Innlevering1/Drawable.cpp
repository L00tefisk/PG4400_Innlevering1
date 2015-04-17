#include "Drawable.h"

SDL_Renderer* Drawable::renderer;
std::vector<SDL_Texture*> Drawable::textureList;


Drawable::Drawable()
{

};

Drawable::~Drawable()
{

}

void Drawable::Init(SDL_Renderer *rend)
{
	if (rend == NULL)
		std::cout << "Renderer is messed up." << std::endl;
	Drawable::renderer = rend;
}

int Drawable::loadResource(const std::string &path)
{
	for (int i = 0; i < loadedResources.size(); i++)
	{
		if (loadedResources[i] == path)
		{
			return i;
			;
		}
	}

	//if (renderer == NULL)
	//	std::cout << "Renderer is messed up." << std::endl;

	SDL_Surface *surface = IMG_Load(path.c_str());
	if (surface == NULL)
		std::cout << "Load failed: " << SDL_GetError() << std::endl;

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
		std::cout << "Texture creation failed." << SDL_GetError() << std::endl;
	// and store them in textureArray
	textureList.push_back(texture);

	loadedResources.push_back(path);
	return textureList.size() - 1;
}
