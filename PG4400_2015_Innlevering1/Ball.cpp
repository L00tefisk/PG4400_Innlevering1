#include "Ball.h"
#include "InputManager.h"

#include "Vector2D.h"
#include "PowerUp.h"

bool Ball::powMagnet; // How does it work?
bool Ball::powSpeedUp;
bool Ball::powSpeedDown;
bool Ball::powSuperBall;
std::vector<Ball>& Ball::balls = GameManager::balls;
Ball::Ball()
{

}

Ball::~Ball()
{
}

void Ball::Init()
{
	rect.x = 200;
	rect.y = 600;
	rect.w = 25;
	rect.h = 25;
	centerX = rect.x + (rect.w / 2);
	centerY = rect.y + (rect.h / 2);
	xSpeed = rand() % 800 - 400;
	ySpeed = rand() % 800 - 400;
	loadResource("../Resources/Balls/ball0001.png", rect);
	relativeHitPositionX = 80;
}

void Ball::Reset()
{
	powMagnet = false; // How does it work?
	powSpeedUp = false;
	powSpeedDown = false;
	powSuperBall = false;
}

void Ball::AddBall(bool onPaddle)
{
	Ball b;
	b.Init();
	b.onPaddle = onPaddle;
	balls.push_back(b);
}

void Ball::Update(const double dt) 
{
	
	if (onPaddle)
	{
		rect.y = GameManager::player.getRectangle().y - rect.h - 1;
		rect.x = GameManager::player.getRectangle().x + relativeHitPositionX;
	}
	else
	{
		rect.x += xSpeed * dt;
		rect.y += ySpeed * dt;
		centerX = rect.x + (rect.w / 2);
		centerY = rect.y + (rect.h / 2);
		
	}
	drawList[textureIDList[0]] = rect;
}

void Ball::ApplyPowerUp(int powType)
{
	int size = balls.size();
	switch (powType)
	{
	case PowerUp::powerType::Magnet:
		powMagnet = true;
		
		break;
	case PowerUp::powerType::Rush:
		for(Ball &b : balls)
			b.ySpeed *= 1.2;
		break;
	case PowerUp::powerType::Slow:
		for(Ball &b : balls)
			b.ySpeed *= 0.8;
		break;
	case PowerUp::powerType::Split:
		for (int i = 0; i < size && balls.size() < 100; i++)
		{
			AddBall(false);
			float xSpeed = balls[i].xSpeed;
			float ySpeed = balls[i].ySpeed;

			balls[balls.size() - 1].rect = balls[i].rect;
			balls[balls.size() - 1].xSpeed = balls[i].ySpeed;
			balls[balls.size() - 1].ySpeed = -balls[i].xSpeed;
			
			AddBall(false);
			balls[balls.size() - 1].rect = balls[i].rect;
			balls[balls.size() - 1].xSpeed = -balls[i].ySpeed;
			balls[balls.size() - 1].ySpeed = balls[i].xSpeed;
		}
		break;
	case PowerUp::powerType::Super:
		powSuperBall = true;
		break;
	}
}
void Ball::ResolveCollision(Vector2D &overlapVector)
{
	Vector2D normalizedVector = overlapVector.getNormalizedVector();
	if (abs(overlapVector.x) < abs(overlapVector.y))
		rect.x += overlapVector.x;
	else
		rect.y += overlapVector.y;
}

void Ball::Fire()
{
	if (!onPaddle)
		return;

	onPaddle = false;
	// mulitiplied by 100 because that seems to be a decent speed.
	xSpeed = ((centerX - GameManager::player.getCenter().x) / GameManager::player.getRectangle().w) * 100;
	ySpeed = -400;
}

