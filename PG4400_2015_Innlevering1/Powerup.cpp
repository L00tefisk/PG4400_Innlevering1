#include  "PowerUp.h"
//#include "GameManager.h"

PowerUp::PowerUp()
{
}

PowerUp::PowerUp(const powerType &type, const SDL_Rect &spawnBox)
{

	size = spawnBox.h;
	rect.w = size;
	rect.h = size;

	rect.x = spawnBox.x + spawnBox.w / 2 - rect.w / 2;
	rect.y = spawnBox.y + spawnBox.h / 2 - rect.h / 2 + ypos;


	this->type = type;
	switch(type)
	{
		case Grow:
			loadResource("../Resources/Power ups/bg_good.png", rect);
			loadResource("../Resources/Power ups/grow.png", rect);
			break;
		case Slow:
			loadResource("../Resources/Power ups/bg_good.png", rect);
			loadResource("../Resources/Power ups/slow.png", rect);
			break;
		case Rocket:
			loadResource("../Resources/Power ups/bg_good.png", rect);
			loadResource("../Resources/Power ups/rocket.png", rect);
			break;
		case Magnet:
			loadResource("../Resources/Power ups/bg_good.png", rect);
			loadResource("../Resources/Power ups/magnet.png", rect);
			break;
		case Super:
			loadResource("../Resources/Power ups/bg_good.png", rect);
			loadResource("../Resources/Power ups/super.png", rect);
			break;
		case Split:
			loadResource("../Resources/Power ups/bg_good.png", rect);
			loadResource("../Resources/Power ups/split.png", rect);
			break;

		case Shrink:
			loadResource("../Resources/Power ups/bg_bad.png", rect);
			loadResource("../Resources/Power ups/shrink.png", rect);
			break;
		case Rush:
			loadResource("../Resources/Power ups/bg_bad.png", rect);
			loadResource("../Resources/Power ups/rush.png", rect);
		case Kill:
			loadResource("../Resources/Power ups/bg_bad.png", rect);
			loadResource("../Resources/Power ups/kill.png", rect);
			break;
	}

	loadResource("../Resources/Power ups/fg.png", rect);
}

PowerUp::~PowerUp () {

}
void PowerUp::Update(const double& dt)
{
	//if(rect.y > 720)//GameManager::WindowHeight)
	ypos += 10;
	rect.y += 10;
	duration -= dt;

	drawList[textureIDList[0]] = rect;
	drawList[textureIDList[1]] = rect;
	drawList[textureIDList[2]] = rect;

}