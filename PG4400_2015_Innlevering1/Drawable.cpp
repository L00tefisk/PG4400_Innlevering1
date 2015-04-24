#include "Drawable.h"

SDL_Renderer* Drawable::renderer;
std::vector<SDL_Texture*> Drawable::textureList;
std::vector<std::string> Drawable::loadedResources;

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

void Drawable::loadResource(const std::string &path, const SDL_Rect& target)
{
	// search if the resource we want is already loaded
	for (int i = 0; i < loadedResources.size(); i++)
	{
		if (loadedResources[i] == path)
		{
			drawList[i] = target;
			textureIDList.push_back(i);
			return;
		}
	}


	SDL_Surface *surface = IMG_Load(path.c_str());
	if (surface == NULL)
		std::cout << "Load failed: " << SDL_GetError() << std::endl;

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
		std::cout << "Texture creation failed." << SDL_GetError() << std::endl;
	// and store them in textureArray
	textureList.push_back(texture);

	loadedResources.push_back(path);
	drawList[textureList.size() - 1] = target;
	textureIDList.push_back(textureList.size() - 1);
}
