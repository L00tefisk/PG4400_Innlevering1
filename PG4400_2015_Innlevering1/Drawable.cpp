#include "Drawable.h"

SDL_Renderer* Drawable::renderer;
std::vector<SDL_Texture*> Drawable::textureList;


Drawable::Drawable()
{
};

Drawable::~Drawable()
{

}

void Drawable::Init(const std::vector<std::string> &imagePathArray, const SDL_Window * window, SDL_Renderer *rend)
{
	renderer = rend;

	for (std::string path : imagePathArray)
	{
		// load textures
		SDL_Surface *surface = IMG_Load(path.c_str());
		if (surface == NULL)
			std::cout << "Load failed." << std::endl;
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

		// and store them in textureArray
		textureList.push_back(texture);
	}
}
