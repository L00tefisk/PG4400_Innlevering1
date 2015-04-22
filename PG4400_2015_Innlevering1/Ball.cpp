#include "Ball.h"
#include "InputManager.h"

#include "Vector2D.h"

Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::Init()
{
	rect.x = 50;
	rect.y = 100;
	rect.w = 10;
	rect.h = 10;
	centerX = rect.x + (rect.w / 2);
	centerY = rect.y + (rect.h / 2);
	xSpeed = 0;
	ySpeed = 0;
	loadResource("../Resources/Balls/ball0002.png", rect);
	onPaddle = true;
}

void Ball::Update(const double &dt) 
{
	if (onPaddle)
	{
		rect.y = 590;
		rect.x = InputManager::GetInstance()->getMouseX() + 35;
	}
	else
	{
		rect.x += xSpeed * dt;
		rect.y += ySpeed * dt;

		if (rect.x < 0 || rect.x + rect.w > 1280)
			xSpeed *= -1;
		if (rect.y < 0 || rect.y + rect.h > 720)
			ySpeed *= -1;
	}

	drawList[textureIDList[0]] = rect;

}

/*

*/
int Ball::Collide(const GameObject &obj, double dt)
{
	//// Separating axis theorem collision detection

	//// First we need two vectors from the rectangle;
	//Vector2D rectangleVector1(obj.getRectangle().x, obj.getRectangle().y); 
	//Vector2D rectangleVector2(obj.getRectangle().x + obj.getRectangle().w, obj.getRectangle().y + obj.getRectangle().h);

	//// And now we need a few vectors to describe 4 points on the circle.
	//Vector2D circleTop(rect.x + (rect.w / 2), rect.y);
	//Vector2D circleBottom(rect.x + (rect.w / 2), rect.y + rect.h);
	//Vector2D circleLeft(rect.x, rect.y + (rect.h / 2));
	//Vector2D circleRight(rect.x + rect.w, rect.y + (rect.h / 2));

	//// Now we'll project these and the circle onto the x axis
	//Vector2D xAxisVector(1, 0);
	//float overlapRectangleX1 = rectangleVector1.project(xAxisVector);
	//float overlapRectangleX2 = rectangleVector2.project(xAxisVector);
	//float overlapCircleX1 = circleLeft.project(xAxisVector);
	//float overlapCircleX2 = circleRight.project(xAxisVector);
	//float minRectangle, maxRectangle;
	//float minCircle, maxCircle;

	//if (overlapRectangleX1 > overlapRectangleX2)
	//{
	//	minRectangle = overlapRectangleX2;
	//	maxRectangle = overlapRectangleX1;
	//}
	//else
	//{
	//	minRectangle = overlapRectangleX1;
	//	maxRectangle = overlapRectangleX2;
	//}

	//if (overlapCircleX1 > overlapCircleX2)
	//{
	//	minCircle = overlapCircleX2;
	//	maxCircle = overlapCircleX1;
	//}
	//else
	//{
	//	minCircle = overlapCircleX2;
	//	maxCircle = overlapCircleX1;
	//}

	//// Check for overlap
	//if (overlapCircleX1 < overlapRectangleX2 ||
	//	overlapCircleX2 > overlapRectangleX1) // Overlap!
	//{

	//}
	//else // We know for sure that there is no overlap
	//{
	//	return 0;
	//}

	//// Now we'll project these and the circle onto the y axis and check for overlap
	//Vector2D yAxisVector(0, 1);
	//float overlapRectangleY1 = rectangleVector1.project(yAxisVector);
	//float overlapRectangleY2 = rectangleVector2.project(yAxisVector);
	//float overlapCircleY1 = circleTop.project(yAxisVector);
	//float overlapCircleY2 = circleTop.project(yAxisVector);


	// tempRect is the balls position in the next frame.
	SDL_Rect tempRect = rect;
	SDL_Rect objRect = obj.getRectangle();
	tempRect.x += xSpeed * dt;
	tempRect.y += ySpeed * dt;
	if (tempRect.x + tempRect.w > objRect.x &&
		tempRect.y + tempRect.h > objRect.y &&
		tempRect.x < objRect.x + objRect.w &&
		tempRect.y < objRect.y + objRect.h)
	{
		return 1;
	}

	// No collision.
	return 0;
}

void Ball::Fire()
{
	if (!onPaddle)
		return;

	onPaddle = false;
	xSpeed = 200;
	ySpeed = -200;
}



/*
// Did the ball enter the object from left or right?
tempRect.x -= xSpeed * dt;
if (tempRect.x + tempRect.w > obj.getRectangle().x &&
tempRect.y + tempRect.h > obj.getRectangle().y &&
tempRect.x < obj.getRectangle().x + obj.getRectangle().w &&
tempRect.y < obj.getRectangle().y + obj.getRectangle().h)
return 1;

// Did the ball enter the object from below or above?
tempRect.x += xSpeed * dt;
tempRect.y -= ySpeed * dt;
if (tempRect.x + tempRect.w > obj.getRectangle().x &&
tempRect.y + tempRect.h > obj.getRectangle().y &&
tempRect.x < obj.getRectangle().x + obj.getRectangle().w &&
tempRect.y < obj.getRectangle().y + obj.getRectangle().h)
return 2;

// The ball must've entered from one of the corners
return 3;
*/