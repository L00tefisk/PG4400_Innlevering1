#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <memory>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <map>


class Drawable
{
public:
	Drawable();
	virtual ~Drawable();
	virtual void Draw() = 0;

	void loadResource(const std::string &path, const SDL_Rect& target);
	static void Init(SDL_Renderer *renderer);
	
protected:
	std::vector<unsigned int> textureIDList;
	std::map<unsigned int, SDL_Rect> drawList;

	static SDL_Renderer *renderer;
	static std::vector<SDL_Texture*> textureList;
	static std::vector<std::string> loadedResources;

private:
};

#endif