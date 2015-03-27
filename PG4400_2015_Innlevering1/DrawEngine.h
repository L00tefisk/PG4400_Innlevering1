#ifndef DRAWENGINE_H
#define DRAWENGINE_H

#include <array>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include "Drawable.h"

class DrawEngine
{
public:
	DrawEngine();

	void Draw(std::shared_ptr<Drawable>);

private:
	SDL_Renderer* renderer;
	static std::shared_ptr<DrawEngine> instance;
	//std::array<SDL_Texture, 4> textures;

};

#endif