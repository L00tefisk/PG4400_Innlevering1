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

	rect.x = spawnBox.x + spawnBox.w / 2;
	rect.y = spawnBox.y + spawnBox.y / 2;


	this->type = type;
	loadResource("../Resources/Power ups/fg.png", rect);
	switch(type)
	{
		case Grow:
			loadResource("../Resources/Power ups/grow.png", rect);
			loadResource("../Resources/Power ups/bg_good.png", rect);
			break;
		case Slow:
			loadResource("../Resources/Power ups/slow.png", rect);
			loadResource("../Resources/Power ups/bg_good.png", rect);
			break;
		case Rocket:
			loadResource("../Resources/Power ups/rocket.png", rect);
			loadResource("../Resources/Power ups/bg_good.png", rect);
			break;
		case Magnet:
			loadResource("../Resources/Power ups/magnet.png", rect);
			loadResource("../Resources/Power ups/bg_good.png", rect);
			break;
		case Super:
			loadResource("../Resources/Power ups/super.png", rect);
			loadResource("../Resources/Power ups/bg_good.png", rect);
			break;
		case Split:
			loadResource("../Resources/Power ups/split.png", rect);
			loadResource("../Resources/Power ups/bg_good.png", rect);
			break;

		case Shrink:
			loadResource("../Resources/Power ups/shrink.png", rect);
			loadResource("../Resources/Power ups/bg_bad.png", rect);
			break;
		case Rush:
			loadResource("../Resources/Power ups/rush.png", rect);
			loadResource("../Resources/Power ups/bg_bad.png", rect);
		case Kill:
			loadResource("../Resources/Power ups/kill.png", rect);
			loadResource("../Resources/Power ups/bg_bad.png", rect);
			break;
	}
}

PowerUp::~PowerUp () {

}

void PowerUp::Update(const double& dt)
{
	//if(rect.y > 720)//GameManager::WindowHeight)

	rect.y += 1 * dt;
	duration -= dt;

	drawList[textureIDList[0]] = rect;
	drawList[textureIDList[1]] = rect;
	drawList[textureIDList[2]] = rect;

}