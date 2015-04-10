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
	renderer = rend;
}

void Drawable::loadResource(const std::string &path)
{

	SDL_Surface *surface = IMG_Load(path.c_str());
	if (surface == NULL)
		std::cout << "Load failed: " << SDL_GetError() << std::endl;

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
		std::cout << "Texture creation failed." << SDL_GetError() << std::endl;
	// and store them in textureArray
	textureList.push_back(texture);
	
	textureID = textureList.size() - 1;
}
