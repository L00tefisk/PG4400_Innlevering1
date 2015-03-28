#include "Paddle.h"
#include "DrawEngine.h"

Paddle::Paddle()
{	
	texPath = "Bats/bat_blue.png";
	locationSizeMap.h = 50;
	locationSizeMap.w = 200;

	//int success = DrawEngine::GetInstance().Draw(locationSizeMap, "../Resources/sdl_bro.bmp");
}
void Paddle::Update()
{
	int success = DrawEngine::GetInstance().Draw(locationSizeMap, "../Resources/sdl_bro.bmp");
}