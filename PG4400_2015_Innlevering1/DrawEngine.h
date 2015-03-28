#ifndef DRAWENGINE_H
#define DRAWENGINE_H

#include <array>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>

class DrawEngine
{
public:
	//~DrawEngine();
	 void init();
	 static DrawEngine& GetInstance()
	 {
		 static DrawEngine instance;
		 return instance;
	 }
	//void Draw(std::shared_ptr<Drawable>);
	int Draw(SDL_Rect locationSizeMap, std::string path);

private:
	DrawEngine();

	SDL_Renderer* renderer;
	SDL_Window* window;
	//std::array<SDL_Texture, 4> textures;

};

#endif