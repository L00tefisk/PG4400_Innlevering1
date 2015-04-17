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
	
protected:
	unsigned short textureID;
	static SDL_Renderer *renderer;
	static std::vector<SDL_Texture *> textureList;
	std::vector<std::string> loadedResources;

private:
};

#endif