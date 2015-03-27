#include "DrawEngine.h"

std::shared_ptr<DrawEngine> DrawEngine::instance = NULL;

DrawEngine::DrawEngine()
{

}

void DrawEngine::Draw(std::shared_ptr<Drawable> draw)
{
	
	draw->Draw();
	SDL_RenderPresent(renderer); // Spør Tomas om vi kan bruke c++11 pointers istadenfor SDL_Renderer*
}